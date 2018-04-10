#include "object_simulator.h"

using namespace MatrixWrapper;

namespace BFL
{
   ObjectSimulator::ObjectSimulator(): _state(STATE_SIZE)
   {
      // initial state
   	_state(1) = X_0;
   	_state(2) = Y_0;
   	_state(3) = Z_0;

      // Create the matrices A and B for the linear system model
      Matrix A(3,3);
      A(1,1) = 1.0;
      A(1,2) = 0.0;
      A(1,3) = 0.0;
      A(2,1) = 0.0;
      A(2,2) = 1.0;
      A(2,3) = 0.0;
      A(3,1) = 0.0;
      A(3,2) = 0.0;
      A(3,3) = 1.0;
      Matrix B(3,3);
      B(1,1) = 1.0;
      B(1,2) = 0.0;
      B(1,3) = 0.0;
      B(2,1) = 0.0;
      B(2,2) = 1.0;
      B(2,3) = 0.0;
      B(3,1) = 0.0;
      B(3,2) = 0.0;
      B(3,3) = 1.0;
      std::vector<Matrix> AB(2);
      AB[0] = A;
      AB[1] = B;
   	// sys noise
   	ColumnVector sys_noise_Mu(STATE_SIZE);
   	sys_noise_Mu(1) = MU_SYSTEM_NOISE_X;
   	sys_noise_Mu(2) = MU_SYSTEM_NOISE_Y;
   	sys_noise_Mu(3) = MU_SYSTEM_NOISE_Z;
   	SymmetricMatrix sys_noise_Cov(STATE_SIZE);
   	sys_noise_Cov(1,1) = SIGMA_SYSTEM_NOISE_X;
   	sys_noise_Cov(1,2) = 0.0;
   	sys_noise_Cov(1,3) = 0.0;
   	sys_noise_Cov(2,1) = 0.0;
   	sys_noise_Cov(2,2) = SIGMA_SYSTEM_NOISE_Y;
   	sys_noise_Cov(2,3) = 0.0;
   	sys_noise_Cov(3,1) = 0.0;
   	sys_noise_Cov(3,2) = 0.0;
   	sys_noise_Cov(3,3) = SIGMA_SYSTEM_NOISE_Z;
      _system_Uncertainty = new Gaussian(sys_noise_Mu, sys_noise_Cov);
      // create the model
      _sys_pdf = new LinearAnalyticConditionalGaussian(AB, *_system_Uncertainty);
      _sys_model = new AnalyticSystemModelGaussianUncertainty(_sys_pdf);
   	// meas noise
      ColumnVector meas_noise_Mu(MEAS_SIZE);
   	meas_noise_Mu(1) = MU_MEAS_NOISE_X;
      meas_noise_Mu(2) = MU_MEAS_NOISE_Y;
      meas_noise_Mu(3) = MU_MEAS_NOISE_Z;
   	SymmetricMatrix meas_noise_Cov(MEAS_SIZE);
      meas_noise_Cov(1,1) = SIGMA_MEAS_NOISE_X;
   	meas_noise_Cov(1,2) = 0.0;
   	meas_noise_Cov(1,3) = 0.0;
   	meas_noise_Cov(2,1) = 0.0;
   	meas_noise_Cov(2,2) = SIGMA_MEAS_NOISE_Y;
   	meas_noise_Cov(2,3) = 0.0;
   	meas_noise_Cov(3,1) = 0.0;
   	meas_noise_Cov(3,2) = 0.0;
   	meas_noise_Cov(3,3) = SIGMA_MEAS_NOISE_Z;
   	_measurement_Uncertainty = new Gaussian(meas_noise_Mu, meas_noise_Cov);
      // create matrix _meas_model for linear measurement model
   	Matrix H(MEAS_SIZE,STATE_SIZE);
      H(1,1) = 1;
      H(1,2) = 0;
      H(1,3) = 0;
      H(2,1) = 0;
      H(2,2) = 1;
      H(2,3) = 0;
      H(3,1) = 0;
      H(3,2) = 0;
      H(3,3) = 1;
      // create the measurement model
      _meas_pdf = new LinearAnalyticConditionalGaussian(H, *_measurement_Uncertainty);
      _meas_model = new LinearAnalyticMeasurementModelGaussianUncertainty(_meas_pdf);
   }

   ObjectSimulator::~ObjectSimulator()
   {
      delete _system_Uncertainty;
      delete _sys_pdf;
   	delete _sys_model;
   	delete _measurement_Uncertainty;
   	delete _meas_pdf;
   	delete _meas_model;
   }

   void ObjectSimulator::Move(ColumnVector inputs)
   {
      _state = _sys_model->Simulate(_state,inputs);
   }

   ColumnVector ObjectSimulator::Measure()
   {
      return _meas_model->Simulate(_state);
   }

   ColumnVector ObjectSimulator::GetState()
   {
      return _state;
   }
}
