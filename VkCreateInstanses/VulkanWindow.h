#ifndef VULKANWINDOW_H
#define VULKANWINDOW_H

#include <QVulkanWindow>
#include <QVulkanInstance>

class CVulkanWindow : public QVulkanWindow
{
    Q_OBJECT

public:


    CVulkanWindow();
    ~CVulkanWindow();
};
#endif // VULKANWINDOW_H
