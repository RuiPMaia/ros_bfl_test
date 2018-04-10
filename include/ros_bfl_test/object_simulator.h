#ifndef MOBILE_ROBOT_HPP
#define MOBILE_ROBOT_HPP

#include <model/analyticsystemmodel_gaussianuncertainty.h>
#include <model/linearanalyticmeasurementmodel_gaussianuncertainty.h>
#include <pdf/gaussian.h>
#include <wrappers/matrix/matrix_wrapper.h>
#include <wrappers/matrix/vector_wrapper.h>

#include "constants.h"

namespace BFL{

/// This is a class simulating a mobile robot
/** The state of the mobile robot is represented with a ColumnVector of three
* elements: the x and y position and the orientation.
* The inputs of the robot are the linear velocity and the angular velocity.
* The mobile robot is equipped with a ultrasonic sensor returning the distance
* to a wall.
* The initial position of the mobile robot is read from mobile_robot_wall_cts.h
* During construction time the measurement model and system model are
* constructed and their properties are read from mobile_robot_wall_cts.h
*/


  class ObjectSimulator
    {
    public:
      // Constructor
      ObjectSimulator();
      ~ObjectSimulator();

      void Move(MatrixWrapper::ColumnVector inputs);
      MatrixWrapper::ColumnVector Measure();
      MatrixWrapper::ColumnVector GetState(); //method only for simulation purposes

    private:
      Gaussian* _system_Uncertainty;
      LinearAnalyticConditionalGaussian* _sys_pdf;
      AnalyticSystemModelGaussianUncertainty* _sys_model;
      Gaussian* _measurement_Uncertainty;
      LinearAnalyticConditionalGaussian* _meas_pdf;
      LinearAnalyticMeasurementModelGaussianUncertainty* _meas_model;
      MatrixWrapper::ColumnVector _state;
    };
}

#endif
