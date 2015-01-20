#include <nodelet/nodelet.h>
#include <pluginlib/class_list_macros.h>
#include "ar_pose/ar_multi.h"

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
    ros::NodeHandle nh = this->getMTPrivateNodeHandle();

    // resolve node(let) name
    std::string name = nh.getUnresolvedNamespace();
    //NODELET_INFO_STREAM("Namespace " << name);
    int pos = name.find_last_of('/');
    name = name.substr(pos + 1);

    NODELET_INFO_STREAM("Initialising nodelet... [" << name << "]");
    controller_.reset(new ARMultiPublisher(nh));

  }
private:
  boost::shared_ptr<ARMultiPublisher> controller_;
};

}

PLUGINLIB_EXPORT_CLASS(ar_pose::ARMultiNodelet,
                       nodelet::Nodelet);

