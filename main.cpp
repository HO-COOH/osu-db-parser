#include <iostream>
#include "OsuDBParser.hpp"
#include <fstream>
#include <memory>

int main()
{

    Db::Osu db{ std::ifstream{ "osu!.db", std::ios_base::binary } };
    Db::Collections collections{ std::ifstream{"collection.db", std::ios_base::binary} };
    Db::Scores scores{ std::ifstream{"scores.db", std::ios_base::binary} };
    
    std::cout << "Parsed "<< db.beatmaps.size() << " maps\n";
    std::cout << "Parsed " << collections.collections.size() << " collections\n";
    std::cout << "Parsed " << scores.beatmapScores.size() << " scores\n";
}