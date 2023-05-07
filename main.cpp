#include "gdal_priv.h"
#include <iostream>

using namespace std;

int main() {
    GDALDataset* dataset;
    GDALAllRegister();
    dataset = GDALDataset::FromHandle(GDALOpen("../data/byte.tif", GA_ReadOnly ));

    double        adfGeoTransform[6];
    printf( "Driver: %s/%s\n",
            dataset->GetDriver()->GetDescription(),
            dataset->GetDriver()->GetMetadataItem( GDAL_DMD_LONGNAME ) );
    printf( "Size is %dx%dx%d\n",
            dataset->GetRasterXSize(), dataset->GetRasterYSize(),
            dataset->GetRasterCount() );
    if( dataset->GetProjectionRef()  != NULL )
        printf( "Projection is `%s'\n", dataset->GetProjectionRef() );
    if( dataset->GetGeoTransform( adfGeoTransform ) == CE_None )
    {
        printf( "Origin = (%.6f,%.6f)\n",
                adfGeoTransform[0], adfGeoTransform[3] );
        printf( "Pixel Size = (%.6f,%.6f)\n",
                adfGeoTransform[1], adfGeoTransform[5] );
    }

    delete dataset;

    return 0;
}
