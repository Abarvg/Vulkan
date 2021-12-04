#ifndef VULKANCOMPUTING_H
#define VULKANCOMPUTING_H


#include <vulkan/vulkan.h>
#include <vulkan/vk_sdk_platform.h>
#include <KHR/khrplatform.h>
#include <QVulkanExtension>
#include <QVulkanInstance>
#include <QVulkanFunctions>
#include <QVulkanDeviceFunctions>

#include <vector>
#include <string.h>
#include <assert.h>
#include <stdexcept>
#include <cmath>


class CVulkanComputing {


public:
    struct Pixel {
        int r, g, b, a;
    };
private:
    const unsigned WIDTH;
    const unsigned HEIGHT;
    const unsigned WORKGROUP_SIZE;
//    unsigned res2,res3,res4,res5;
    QVulkanInstance instance;
    QVulkanFunctions* f_instance;

    VkDebugReportCallbackEXT debugReportCallback;

    VkPhysicalDevice physicalDevice;
public:
    VkDevice device;

    QVulkanDeviceFunctions* df_instance;
private:
    VkPipeline pipeline;
    VkPipelineLayout pipelineLayout;


    VkCommandPool commandPool;
    VkCommandBuffer commandBuffer;

    VkDescriptorPool descriptorPool;
    VkDescriptorSet descriptorSet;
    VkDescriptorSetLayout descriptorSetLayout;
    VkShaderModule computeShaderModule;
    VkBuffer buffer;
public:
    VkDeviceMemory bufferMemory;

    uint32_t bufferSize;
private:
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


    uint32_t getComputeQueueFamilyIndex();
    uint32_t findMemoryType(uint32_t memoryTypeBits, VkMemoryPropertyFlags properties);

    void cleanup();

};
#endif // VULKANCOMPUTING_H
