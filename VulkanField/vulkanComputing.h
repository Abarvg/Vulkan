#ifndef VULKANCOMPUTING_H
#define VULKANCOMPUTING_H


#include <vulkan/vulkan.h>

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
    VkInstance instance;

    VkDebugReportCallbackEXT debugReportCallback;

    VkPhysicalDevice physicalDevice;

    VkDevice device;

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

    std::vector<const char *> enabledLayers;

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

    void cleanup();

};
#endif // VULKANCOMPUTING_H
