#include "simulation_player/simulation_player.hpp"

namespace simulation_player
{
  SimulationPlayer::SimulationPlayer(QWidget *parent)
    : Panel{parent}
    , ui_(std::make_unique<Ui::gui>())
    , node_{nullptr}
  {
    // Extend the widget with all attributes and children from UI file
    ui_->setupUi(this);

    // Init rclcpp node
    auto options = rclcpp::NodeOptions();
    node_ = std::make_shared<rclcpp::Node>("simulation_player", options);

    forward_pub_ = node_->create_publisher<std_msgs::msg::Bool>("forward_step", 1);
    backward_pub_ = node_->create_publisher<std_msgs::msg::Bool>("backward_step", 1);
    start_pub_ = node_->create_publisher<std_msgs::msg::Bool>("start_simulation", 1);
    stop_pub_ = node_->create_publisher<std_msgs::msg::Bool>("stop_simulation", 1);
    step_pub_ = node_->create_publisher<std_msgs::msg::Float32>("step_size", 1);

    // Prepare msg
    msg_.data = true;
  }

  SimulationPlayer::~SimulationPlayer()
  {
  }
    void SimulationPlayer::load(const rviz_common::Config &config)
    {
      Panel::load(config);
    }

    void SimulationPlayer::save(rviz_common::Config config) const
    {
      Panel::save(config);
    }

    void SimulationPlayer::on_forwardButton_clicked()
    {
      forward_pub_->publish(msg_);
    }

    void SimulationPlayer::on_backwardButton_clicked()
    {
      backward_pub_->publish(msg_);
    }

    void SimulationPlayer::on_startButton_clicked()
    {
      start_pub_->publish(msg_);
    }

    void SimulationPlayer::on_stopButton_clicked()
    {
      stop_pub_->publish(msg_);
    }

    void SimulationPlayer::on_setStepButton_clicked()
    {
      step_msg_.data = ui_->stepSizeBox->value();
      step_pub_->publish(step_msg_);
    }
} // simulation_player

#include <pluginlib/class_list_macros.hpp>
PLUGINLIB_EXPORT_CLASS(simulation_player::SimulationPlayer, rviz_common::Panel)
