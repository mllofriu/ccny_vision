#ifndef AR_MULTI_NODELET_H
#define AR_MULTI_NODELET_H

#include <nodelet/nodelet.h>
#include <pluginlib/class_list_macros.h>
#include "ar_multi.h"

namespace ar_pose
{

/**
 * @brief Nodelet-wrapper of the ar_multi node
 */
class ARMultiNodelet : public nodelet::Nodelet
{
public:
  ARMultiNodelet(){};
  ~ARMultiNodelet(){}

  /**
   * @brief Initialise the nodelet
   *
   * This function is called, when the nodelet manager loads the nodelet.
   */
  virtual void onInit()
  {
    ros::NodeHandle nh = this->getPrivateNodeHandle();

    // resolve node(let) name
    std::string name = nh.getUnresolvedNamespace();
    int pos = name.find_last_of('/');
    name = name.substr(pos + 1);

    NODELET_INFO_STREAM("Initialising nodelet... [" << name << "]");
    controller_.reset(new ARMultiPublisher(nh));

    // Initialises the controller
    if (controller_->init())
    {
      NODELET_INFO_STREAM("Nodelet initialised. [" << name << "]");
    }
    else
    {
      NODELET_ERROR_STREAM("Couldn't initialise nodelet! Please restart. [" << name << "]");
    }
  }
private:
  boost::shared_ptr<ARMultiPublisher> controller_;
};

}

PLUGINLIB_EXPORT_CLASS(kobuki::BumpBlinkControllerNodelet,
                       nodelet::Nodelet);

#endif // AR_MULTI_NODELET_H
