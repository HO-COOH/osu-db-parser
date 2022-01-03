#include <fstream>
#include <vector>
#include <utility>
#include <cassert>

struct Db
{
    template<typename Underlying>
    class TrivialParsable
    {
        Underlying value{};
    public:
        TrivialParsable(unsigned char const*& ptr) :
            value(*reinterpret_cast<Underlying const*>(ptr))
        {
            ptr += sizeof(Underlying);
        }

        TrivialParsable() = default;

        operator Underlying() const
        {
            return value;
        }
    };
    using Byte = TrivialParsable<unsigned char>;
    using Short = TrivialParsable<short>;
    using Int = TrivialParsable<int32_t>;
    using Long = TrivialParsable<int64_t>;

    class ULEB128
    {
        uint64_t value{};
    public:
        ULEB128(unsigned char const* ptr)
        {
            //TODO
        }

        operator uint64_t() const
        {
            return value;
        }
    };

    using Single = TrivialParsable<float>;
    using Double = TrivialParsable<double>;
    using Boolean = TrivialParsable<unsigned char>;

    class String : public std::string
    {
    public:
        String(unsigned char const*& ptr)
        {

        }
    };

    class IntDoublePair : public std::pair<Int, Double>
    {
    public:
        IntDoublePair(unsigned char const*& ptr) : std::pair<Int, Double>{}
        {
            if (ptr[0] != 0x08)
                assert(false); //First byte is 0x08
            ++ptr;
            first = *reinterpret_cast<Int const*>(ptr);
            ptr += sizeof(Int);

            if (ptr[0] != 0x0d)
                assert(false); //The byte is 0x0d
            ++ptr;
            second = *reinterpret_cast<Double const*>(ptr);
        }
    };

    class TimingPoint
    {
        Double bpm;
        Double offset; //in milliseconds
        Boolean uninherited; //false -> inherited
    public:
        TimingPoint(unsigned char const* ptr)
            : bpm(*reinterpret_cast<Double const*>(ptr)),
            offset(*reinterpret_cast<Double const*>(ptr[sizeof(Double)])),
            uninherited(*reinterpret_cast<Boolean const*>(ptr[sizeof(Double) * 2]))
        {
        }
    };

    class DateTime
    {
        int64_t ticks{}; //amount of invervals of 100 nanoseconds since midnight Jan1, 0001 UTC
    public:
        DateTime(unsigned char const* ptr)
            : ticks{*reinterpret_cast<int64_t const*>(ptr)}
        {
        }
    };

    class Beatmap
    {
    public:
        enum class RankStatus : unsigned char
        {
            Unknown = 0,
            Unsubmitted = 1,
            Pending = 2,
            Unused = 3,
            Ranked = 4,
            Approved = 5,
            Qualified = 6,
            Loved = 7
        };

        enum class Mode : unsigned char
        {
            Std = 0x00,
            Taiko = 0x01,
            Ctb = 0x02,
            Mania = 0x03
        };
    private:
        
        String artistName;
        String artistNameUnicode;
        String songTitle;
        String songTitleUnicode;
        String creator;
        String difficulty;
        String audioFileName;
        String md5;
        String osuFileName;
        RankStatus rankStatus;
        Short numHitCircles;
        Short numSliders;
        Short numSpinners;
        Long lastModified;
        Single approachRate;
        Single circleSize;
        Single hpDrainRate;
        Single overallDifficulty;
        Double sliderVelocity;
        std::vector<IntDoublePair> stdModStarRating;    //mod <=> star rating in std
        std::vector<IntDoublePair> taikoModStarRating;  //mod <=> star rating in taiko
        std::vector<IntDoublePair> maniaModStarRating;  //mod <=> star rating in mania
        Int drainTime; //in seconds
        Int totalTime; //in milliseconds
        Int previewTime; //in milliseconds
        std::vector<TimingPoint> timingPoints;
        Int difficultyId;
        Int beatmapId;
        Int threadId;
        Byte stdGrade;
        Byte taikoGrade;
        Byte ctbGrade;
        Byte maniaGrade;
        Short localOffset;
        Single stackLeniency;
        Mode mode;
        String songSource;
        String songTags;
        Short onlineOffset;
        String font;
        Boolean unplayed;
        Long lastPlayed;
        Boolean isOsz2;
        String folderName;
        Long lastChecked; //last time when beatmap was checked against osu! repository
        Boolean ignoreBitmapSound;
        Boolean ignoreSkin;
        Boolean disableStoryboard;
        Boolean disableVideo;
        Boolean visualOverride;
        //Int lastModified;
        Byte maniaScrollSpeed;
    public:
        Beatmap(unsigned char const* ptr, Int version)
        {
            
        }
    };

    enum class UserPermission
    {
        None = 0,
        Normal = 1,
        Moderator = 2,
        Supporter = 4,
        Friend = 8,
        Peppy = 16,
        WorldCupStaff = 32
    };

    Int version{};

    Int folderCount{};

    Boolean accountUnlocked{};

    DateTime unlockAccountDate;

    String playerName;

    Int numBeatmaps{};

    std::vector<Beatmap> beatmaps;

    UserPermission userPermission;
    
};