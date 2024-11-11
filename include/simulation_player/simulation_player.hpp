#pragma once

// ROS2
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/bool.hpp>
// RVIZ2
#include <rviz_common/panel.hpp>
// Qt
#include <QtWidgets>
// STL
#include <memory>

#include <std_msgs/msg/float32.hpp>
/** 
 *  Include header generated from ui file
 *  Note that you will need to use add_library function first
 *  in order to generate the header file from ui.
 */
#include <ui_simulation_player.h>

namespace simulation_player
{
  class SimulationPlayer : public rviz_common::Panel
  {
    Q_OBJECT
  public:
    explicit SimulationPlayer(QWidget *parent = nullptr);
    ~SimulationPlayer();

    /// Load and save configuration data
    virtual void load(const rviz_common::Config &config) override;
    virtual void save(rviz_common::Config config) const override;

  private Q_SLOTS:
    void on_forwardButton_clicked();
    void on_backwardButton_clicked();
    void on_startButton_clicked();
    void on_stopButton_clicked();
    void on_setStepButton_clicked();

  private:
    std::unique_ptr<Ui::gui> ui_;
    rclcpp::Node::SharedPtr node_;

  protected:
    rclcpp::Publisher<std_msgs::msg::Bool>::SharedPtr forward_pub_;
    rclcpp::Publisher<std_msgs::msg::Bool>::SharedPtr backward_pub_;
    rclcpp::Publisher<std_msgs::msg::Bool>::SharedPtr start_pub_;
    rclcpp::Publisher<std_msgs::msg::Bool>::SharedPtr stop_pub_;
    rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr step_pub_;
    std_msgs::msg::Bool msg_;
    std_msgs::msg::Float32 step_msg_;
  };
} // simulation_player
