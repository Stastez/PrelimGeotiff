#include "gdal_priv.h"
#include <iostream>

using namespace std;

int main() {
    GDALDataset* poDataset;
    GDALAllRegister();
    const GDALAccess eAccess = GA_ReadOnly;
    poDataset = GDALDataset::FromHandle(GDALOpen( "../data/byte.tif", eAccess ));

    poDataset->GetRasterBand(1);

    cout << "hi";

    delete poDataset;

    return 0;
}
