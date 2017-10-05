#ifndef OPEN_BASE_CONTROLLER_CUSTOM_CONTROLLER_H
#define OPEN_BASE_CONTROLLER_CUSTOM_CONTROLLER_H

#include <algorithm>
#include <cstddef>
#include <vector>
#include <string>

#include <sys/mman.h>

#include <ros/node_handle.h>
#include <hardware_interface/joint_command_interface.h>
#include <controller_interface/controller.h>
#include <trajectory_msgs/JointTrajectoryPoint.h>
#include <sensor_msgs/JointState.h>
#include <pluginlib/class_list_macros.h>

#include <Eigen/Core>

#include <kdl/solveri.hpp>
#include <kdl/frames.hpp>
#include <kdl/jntarray.hpp>
#include <kdl/jntarrayvel.hpp>
#include <kdl/jacobian.hpp>
#include <kdl/chain.hpp>
#include <kdl/framevel.hpp>
#include <kdl/chainjnttojacsolver.hpp>
#include <kdl/chainfksolverpos_recursive.hpp>
#include <kdl/chainidsolver_recursive_newton_euler.hpp>
#include <kdl_parser/kdl_parser.hpp>

namespace open_base_controller {

    class CustomController: public controller_interface::Controller<hardware_interface::EffortJointInterface> {

        ros::NodeHandle node_;

	hardware_interface::EffortJointInterface *robot_;
	std::vector<hardware_interface::JointHandle> jointVector;

	ros::Subscriber sub_command_;

	KDL::ChainIdSolver_RNE *idsolver;

	KDL::JntArray q;
	KDL::JntArray dq;
	KDL::JntArray v;

	KDL::JntArray qr;
	KDL::JntArray dqr;
	KDL::JntArray ddqr;

	KDL::JntArray torque;

	KDL::Wrenches fext;

	Eigen::MatrixXd Kp;
	Eigen::MatrixXd Kd;

	void commandCallBack(const trajectory_msgs::JointTrajectoryPoint::ConstPtr &referencePoint);

	int i;

	int j = -1;

	double max = 0;

	double u[1000] = {
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02,
	    -0.02
	};

	public:
	CustomController(void);
	~CustomController(void);

	bool init(hardware_interface::EffortJointInterface *robot, ros::NodeHandle &n);
	void starting(const ros::Time& time);
	void update(const ros::Time& time,const ros::Duration& duration);
    };
}
#endif
