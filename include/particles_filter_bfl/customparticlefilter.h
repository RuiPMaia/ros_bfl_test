#ifndef CUSTOMPARTICLEFILTER_H
#define CUSTOMPARTICLEFILTER_H

#include <filter/bootstrapfilter.h>

using namespace BFL;

class CustomParticleFilter : public BootstrapFilter<MatrixWrapper::ColumnVector,MatrixWrapper::ColumnVector>
{
public:
    CustomParticleFilter(MCPdf<MatrixWrapper::ColumnVector> * prior,
                          int resampleperiod = 0,
                          double resamplethreshold = 0,
                          int resamplescheme = DEFAULT_RS);

    vector<WeightedSample<MatrixWrapper::ColumnVector> > getNewSamples();
    //vector<WeightedSample<MatrixWrapper::ColumnVector> > getOldSamples();

};

#endif // CUSTOMPARTICLEFILTER_H
