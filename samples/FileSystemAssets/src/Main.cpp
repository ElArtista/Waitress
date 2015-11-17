#include <iostream>
#include <Waitress/Waitress.hpp>

int main(int argc, char* argv[])
{
    (void) argc;
    (void) argv;

    using namespace Waitress;
    ResMan<FileSystemDatastore> resMan;

    // Path to the asset folder
    std::string assetFolder = "res";

    // Try to load file that does not exist
    auto missing = resMan.Load(assetFolder + "/" + "non_existing_asset.txt");
    std::cout << "Tried to load non existing file and got: " << missing << std::endl;

    // Load file that does exist
    std::string file1 = "asset1.txt";
    auto buf1 = resMan.Load(assetFolder + "/" + file1);
    std::cout << "Loaded file "<< file1 << " size: " << buf1->size() << std::endl;

    // Re-retrieve loaded file
    auto buf2 = resMan.Get(assetFolder + "/" + file1);
    std::cout << "Retrieved preloaded file: " << file1 << " size: " << buf2->size() << std::endl;

    // Unload file
    resMan.Unload(assetFolder + "/" + file1);

    // Try to retrieve unloaded file
    auto buf3 = resMan.Get(assetFolder + "/" + file1);
    std::cout << "Tried to retrieve unloaded file and got: " << buf3 << std::endl;
    
    return 0;
}
