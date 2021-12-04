#ifndef CCOMPUTEAPPLICATION_H
#define CCOMPUTEAPPLICATION_H

#include <vulkan/vulkan.h>

#include <fstream>
#include <iostream>
#include <vector>
#include <string.h>
#include <assert.h>
#include <stdexcept>
#include <cmath>

class CComputeApplication {
public:
    struct Pixel {
        float r, g, b, a;
    };
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
    void run();

    void createInstance();
    static VKAPI_ATTR VkBool32 VKAPI_CALL debugReportCallbackFn(VkDebugReportFlagsEXT, VkDebugReportObjectTypeEXT, uint64_t, size_t, int32_t, const char* pLayerPrefix, const char* pMessage, void*){
        printf("Debug Report: %s: %s\n", pLayerPrefix, pMessage);
        return VK_FALSE;
    }
    void findPhysicalDevice();
    uint32_t getComputeQueueFamilyIndex();
    void createDevice();
    uint32_t findMemoryType(uint32_t memoryTypeBits, VkMemoryPropertyFlags properties);
    void createBuffer();
    void createDescriptorSetLayout();
    void createDescriptorSet();
    uint32_t* readFile(uint32_t& length, const char* filename);
    void createComputePipeline();
    void createCommandBuffer();

    void runCommandBuffer();

    void saveRenderedImage();
    void cleanup();
    CComputeApplication();
    ~CComputeApplication();
};
#endif // CCOMPUTEAPPLICATION_H
