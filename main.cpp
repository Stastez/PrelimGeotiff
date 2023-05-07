#include "gdal_priv.h"
#include <iostream>

int main() {
    //Drivers must be registered first, otherwise GetDriver[...] will not find any drivers
    GDALRegister_GTiff();

    //Driver facilitates FileIO
    GDALDriver* driver = GetGDALDriverManager()->GetDriverByName("GTiff");
    if (driver == nullptr) { std::cout << "Could not get driver!" << std::endl; exit(-1); }
    if (!CSLFetchBoolean(GDALGetMetadata(driver, nullptr), GDAL_DCAP_CREATE, FALSE)) { std::cout << "Driver does not support creation!" << std::endl; exit(-2); }

    //Dataset manages all possible data channels (color, geographic projection type, ...)
    const int rasterSize = 25;
    const int numChannels = 3;
    GDALDataset* dataset = driver->Create("../test.tiff", rasterSize, rasterSize, numChannels, GDT_Byte, nullptr);

    //GDT_Byte and GByte are aliases for uint8
    auto rasterArray = new GByte*[numChannels];
    for (int i = 0; i < numChannels; i++) {
        rasterArray[i] = new GByte[rasterSize*rasterSize];
    }

    for (int i = 0; i < rasterSize * rasterSize; i++) {
        rasterArray[0][i] = (i % 3 == 0) ? 255 : 0;
        rasterArray[1][i] = (i % 3 == 1) ? 255 : 0;
        rasterArray[2][i] = (i % 3 == 2) ? 255 : 0;
    }

    //Raster band is synonymous with channels, contains actual (color) data
    auto channelArray = new GDALRasterBand*[numChannels];
    for (int i = 0; i < numChannels; i++) {
        channelArray[i] = dataset->GetRasterBand(i+1);
        //RasterIO call CAN reformat data (e.g. one dimensional array to two dimensional array) via parameters 7+, as used here
        channelArray[i]->RasterIO(GF_Write, 0, 0, rasterSize, rasterSize, rasterArray[i], rasterSize, rasterSize, GDT_Byte, 0, 0, nullptr);
    }

    std::cout << "Root directory should now contain <<test.tiff>>. This should display an RGB checkerboard." << std::endl;

    //<delete dataset> does not work correctly according to docs
    GDALClose(dataset);

    return 0;
}
