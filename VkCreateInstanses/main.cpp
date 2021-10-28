#include "VulkanWindow.h"
#include <QApplication>
#include <QVulkanWindow>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CVulkanWindow w;
    QVulkanInstance inst;
#ifndef Q_OS_ANDROID
    inst.setLayers(QByteArrayList() << "VK_LAYER_LUNARG_standard_validation");
#else
    inst.setLayers(QByteArrayList()
                   << "VK_LAYER_GOOGLE_threading"
                   << "VK_LAYER_LUNARG_parameter_validation"
                   << "VK_LAYER_LUNARG_object_tracker"
                   << "VK_LAYER_LUNARG_core_validation"
                   << "VK_LAYER_LUNARG_image"
                   << "VK_LAYER_LUNARG_swapchain"
                   << "VK_LAYER_GOOGLE_unique_objects");
#endif

    if (!inst.create())
        qFatal("Failed to create Vulkan instance: %d", inst.errorCode());

    w.setGeometry(100,100,350,350);
    w.setVulkanInstance(&inst);
//    w.show();
    return a.exec();
}
