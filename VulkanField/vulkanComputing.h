#ifndef VULKANCOMPUTING_H
#define VULKANCOMPUTING_H


#include <vulkan/vulkan.h>
#include <vulkan/vk_sdk_platform.h>
#include <KHR/khrplatform.h>
#include <QVulkanExtension>
#include <QVulkanInstance>
#include <QVulkanFunctions>

#include <vector>
#include <string.h>
#include <assert.h>
#include <stdexcept>
#include <cmath>


class CVulkanComputing {
private:
    struct Pixel {
        float r, g, b, a;
    };
    const int WIDTH;
    const int HEIGHT;
    const int WORKGROUP_SIZE;
    QVulkanInstance instance;
    QVulkanFunctions* f_instance = instance.functions();

    VkDebugReportCallbackEXT debugReportCallback;

    VkPhysicalDevice physicalDevice;

    VkDevice device;
    QVulkanDeviceFunctions* df_instance = instance.deviceFunctions(device);

    VkPipeline pipeline;
    VkPipelineLayout pipelineLayout;
    VkShaderModule computeShaderModule;

    VkCommandPool commandPool;
    VkCommandBuffer commandBuffer;

    VkDescriptorPool descriptorPool;
    VkDescriptorSet descriptorSet;
    VkDescriptorSetLayout descriptorSetLayout;

    VkBuffer buffer;
    VkDeviceMemory bufferMemory;

    uint32_t bufferSize;

    QByteArrayList enabledLayers;

    VkQueue queue;

    uint32_t queueFamilyIndex;

public:
    CVulkanComputing();
    ~CVulkanComputing();

    void run();
    void createInstance();
    void findPhysicalDevice();
    void createDevice();
    void createBuffer();
    void createDescriptorSetLayout();
    void createDescriptorSet();
    void createComputePipeline();
    void createCommandBuffer();


    void runCommandBuffer();

    void saveRenderedImage();

    uint32_t getComputeQueueFamilyIndex();
    uint32_t findMemoryType(uint32_t memoryTypeBits, VkMemoryPropertyFlags properties);

    void cleanup();

};
#endif // VULKANCOMPUTING_H
