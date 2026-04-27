#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"

using namespace std::chrono_literals;

class FakeRobotMover : public rclcpp::Node
{
public:
    FakeRobotMover() : Node("fake_robot_mover"), step_(0)
    {
        publisher_ =
            this->create_publisher<geometry_msgs::msg::Twist>("/cmd_vel", 10);

        timer_ = this->create_wall_timer(
            2s,
            std::bind(&FakeRobotMover::move_robot, this));

        RCLCPP_INFO(this->get_logger(), "Fake Robot Mover Started");
    }

private:
    void move_robot()
    {
        geometry_msgs::msg::Twist msg;

        switch(step_)
        {
            case 0:
                msg.linear.x = 0.5;
                RCLCPP_INFO(this->get_logger(), "Moving Forward");
                break;

            case 1:
                msg.linear.x = 0.0;
                RCLCPP_INFO(this->get_logger(), "Stopping");
                break;

            case 2:
                msg.angular.z = 0.8;
                RCLCPP_INFO(this->get_logger(), "Turning Left");
                break;

            case 3:
                msg.linear.x = 0.5;
                RCLCPP_INFO(this->get_logger(), "Moving Forward Again");
                break;

            case 4:
                msg.angular.z = -0.8;
                RCLCPP_INFO(this->get_logger(), "Turning Right");
                break;

            default:
                msg.linear.x = 0.0;
                msg.angular.z = 0.0;
                RCLCPP_INFO(this->get_logger(), "Final Stop");
                step_ = -1;
                break;
        }

        publisher_->publish(msg);
        step_++;
    }

    int step_;

    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<FakeRobotMover>());
    rclcpp::shutdown();
    return 0;
}
