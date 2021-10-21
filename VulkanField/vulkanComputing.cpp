
#include <vulkan/vulkan.h>
#include <vulkan/vk_sdk_platform.h>
#include <KHR/khrplatform.h>
#include <QVulkanExtension>
#include <QVulkanInstance>
#include <qvulkaninstance.h>

#include <vector>
#include <string.h>
#include <assert.h>
#include <stdexcept>
#include <cmath>
#include "vulkanComputing.h"

#ifdef NDEBUG
const bool enableValidationLayers = true;
#else
const bool enableValidationLayers = false;
#endif

#define VK_CHECK_RESULT(f) 																				\
{																										\
    VkResult res = (f);																					\
    if (res != VK_SUCCESS)																				\
    {																									\
        printf("Fatal : VkResult is %d in %s at line %d\n", res,  __FILE__, __LINE__); \
        assert(res == VK_SUCCESS);																		\
    }																									\
}


CVulkanComputing::CVulkanComputing()
     :WIDTH(350),
      HEIGHT(350),
      WORKGROUP_SIZE(32)
{




};

void CVulkanComputing::run() {
    bufferSize = sizeof(Pixel) * WIDTH * HEIGHT;

    createInstance();
    findPhysicalDevice();
    createDevice();
    createBuffer();
//    createDescriptorSetLayout();
//    createDescriptorSet();
//    createComputePipeline();
//    createCommandBuffer();

//    runCommandBuffer();

//    saveRenderedImage();

//    cleanup();
}

static VKAPI_ATTR VkBool32 VKAPI_CALL debugReportCallbackFn(
    VkDebugReportFlagsEXT                       flags,
    VkDebugReportObjectTypeEXT                  objectType,
    uint64_t                                    object,
    size_t                                      location,
    int32_t                                     messageCode,
    const char*                                 pLayerPrefix,
    const char*                                 pMessage,
    void*                                       pUserData) {

    printf("Debug Report: %s: %s\n", pLayerPrefix, pMessage);

    return VK_FALSE;
}


void CVulkanComputing::createInstance(){
    std::vector<const char *> enabledExtensions;

    if (enableValidationLayers) {
        uint32_t layerCount;
        vkEnumerateInstanceLayerProperties(&layerCount, NULL);

        std::vector<VkLayerProperties> layerProperties(layerCount);
        vkEnumerateInstanceLayerProperties(&layerCount, layerProperties.data());

        bool foundLayer = false;
        for (VkLayerProperties prop : layerProperties) {

            if (strcmp("VK_LAYER_LUNARG_standard_validation", prop.layerName) == 0) {
                foundLayer = true;
                break;
            }

        }

        if (!foundLayer) {
            throw std::runtime_error("Layer VK_LAYER_LUNARG_standard_validation not supported\n");
        }
        enabledLayers.push_back("VK_LAYER_LUNARG_standard_validation"); // Alright, we can use this layer.

        uint32_t extensionCount;

        vkEnumerateInstanceExtensionProperties(NULL, &extensionCount, NULL);
        std::vector<VkExtensionProperties> extensionProperties(extensionCount);
        vkEnumerateInstanceExtensionProperties(NULL, &extensionCount, extensionProperties.data());

        bool foundExtension = false;
        for (VkExtensionProperties prop : extensionProperties) {
            if (strcmp(VK_EXT_DEBUG_REPORT_EXTENSION_NAME, prop.extensionName) == 0) {
                foundExtension = true;
                break;
            }

        }

        if (!foundExtension) {
            throw std::runtime_error("Extension VK_EXT_DEBUG_REPORT_EXTENSION_NAME not supported\n");
        }
        enabledExtensions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
    }

    VkApplicationInfo applicationInfo = {};
    applicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    applicationInfo.pApplicationName = "Vulkf";
    applicationInfo.applicationVersion = 0;
    applicationInfo.pEngineName = "";
    applicationInfo.engineVersion = 0;
    applicationInfo.apiVersion = VK_API_VERSION_1_0;;

    VkInstanceCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.flags = 0;
    createInfo.pApplicationInfo = &applicationInfo;
    createInfo.enabledLayerCount = enabledLayers.size();
    createInfo.ppEnabledLayerNames = enabledLayers.data();
    createInfo.enabledExtensionCount = enabledExtensions.size();
    createInfo.ppEnabledExtensionNames = enabledExtensions.data();

    VK_CHECK_RESULT(vkCreateInstance(&createInfo, VK_NULL_HANDLE, &instance));
    if (enableValidationLayers) {
        VkDebugReportCallbackCreateInfoEXT createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
        createInfo.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT | VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT;
        createInfo.pfnCallback = &debugReportCallbackFn;


        auto vkCreateDebugReportCallbackEXT = (PFN_vkCreateDebugReportCallbackEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugReportCallbackEXT");
        if (vkCreateDebugReportCallbackEXT == nullptr) {
            throw std::runtime_error("Could not load vkCreateDebugReportCallbackEXT");
        }

        VK_CHECK_RESULT(vkCreateDebugReportCallbackEXT(instance, &createInfo, NULL, &debugReportCallback));
    }

}

void CVulkanComputing::findPhysicalDevice() {
    uint32_t deviceCount;
    vkEnumeratePhysicalDevices(instance, &deviceCount, NULL);
    if (deviceCount == 0) {
        throw std::runtime_error("could not find a device with vulkan support");
    }

    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

    for (VkPhysicalDevice device : devices) {
        if (true) {
            physicalDevice = device;
            break;
        }
    }
}

uint32_t CVulkanComputing::getComputeQueueFamilyIndex() {
    uint32_t queueFamilyCount;

    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, NULL);

    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, queueFamilies.data());


    uint32_t i = 0;
    for (; i < queueFamilies.size(); ++i) {
        VkQueueFamilyProperties props = queueFamilies[i];

        if (props.queueCount > 0 && (props.queueFlags & VK_QUEUE_COMPUTE_BIT)) {
            break;
        }
    }

    if (i == queueFamilies.size()) {
        throw std::runtime_error("could not find a queue family that supports operations");
    }

    return i;
}


void CVulkanComputing::createDevice() {

    VkDeviceQueueCreateInfo queueCreateInfo = {};
    queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueFamilyIndex = getComputeQueueFamilyIndex();
    queueCreateInfo.queueFamilyIndex = queueFamilyIndex;
    queueCreateInfo.queueCount = 1;
    float queuePriorities = 1.0;
    queueCreateInfo.pQueuePriorities = &queuePriorities;

    VkDeviceCreateInfo deviceCreateInfo = {};

    VkPhysicalDeviceFeatures deviceFeatures = {};

    deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    deviceCreateInfo.enabledLayerCount = enabledLayers.size();  // need to specify validation layers here as well.
    deviceCreateInfo.ppEnabledLayerNames = enabledLayers.data();
    deviceCreateInfo.pQueueCreateInfos = &queueCreateInfo; // when creating the logical device, we also specify what queues it has.
    deviceCreateInfo.queueCreateInfoCount = 1;
    deviceCreateInfo.pEnabledFeatures = &deviceFeatures;

    VK_CHECK_RESULT(vkCreateDevice(physicalDevice, &deviceCreateInfo, NULL, &device)); // create logical device.

    vkGetDeviceQueue(device, queueFamilyIndex, 0, &queue);
}


uint32_t CVulkanComputing::findMemoryType(uint32_t memoryTypeBits, VkMemoryPropertyFlags properties) {
    VkPhysicalDeviceMemoryProperties memoryProperties;

    vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memoryProperties);

    /*
    How does this search work?
    See the documentation of VkPhysicalDeviceMemoryProperties for a detailed description.
    */
    for (uint32_t i = 0; i < memoryProperties.memoryTypeCount; ++i) {
        if ((memoryTypeBits & (1 << i)) &&
            ((memoryProperties.memoryTypes[i].propertyFlags & properties) == properties))
            return i;
    }
    return -1;
}

void CVulkanComputing::createBuffer() {

    VkBufferCreateInfo bufferCreateInfo = {};
    bufferCreateInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferCreateInfo.size = bufferSize;
    bufferCreateInfo.usage = VK_BUFFER_USAGE_STORAGE_BUFFER_BIT;
    bufferCreateInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    VK_CHECK_RESULT(vkCreateBuffer(device, &bufferCreateInfo, NULL, &buffer));

    VkMemoryRequirements memoryRequirements;
    vkGetBufferMemoryRequirements(device, buffer, &memoryRequirements);

    VkMemoryAllocateInfo allocateInfo = {};
    allocateInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocateInfo.allocationSize = memoryRequirements.size;
    allocateInfo.memoryTypeIndex = findMemoryType(
        memoryRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_COHERENT_BIT | VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT);

    VK_CHECK_RESULT(vkAllocateMemory(device, &allocateInfo, NULL, &bufferMemory));

    VK_CHECK_RESULT(vkBindBufferMemory(device, buffer, bufferMemory, 0));
}

void CVulkanComputing::createDescriptorSetLayout() {

    /*
    Here we specify a binding of type VK_DESCRIPTOR_TYPE_STORAGE_BUFFER to the binding point
    0. This binds to

      layout(std140, binding = 0) buffer buf

    in the compute shader.
    */
    VkDescriptorSetLayoutBinding descriptorSetLayoutBinding = {};
    descriptorSetLayoutBinding.binding = 0;
    descriptorSetLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
    descriptorSetLayoutBinding.descriptorCount = 1;
    descriptorSetLayoutBinding.stageFlags = VK_SHADER_STAGE_COMPUTE_BIT;

    VkDescriptorSetLayoutCreateInfo descriptorSetLayoutCreateInfo = {};
    descriptorSetLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    descriptorSetLayoutCreateInfo.bindingCount = 1;
    descriptorSetLayoutCreateInfo.pBindings = &descriptorSetLayoutBinding;


    VK_CHECK_RESULT(vkCreateDescriptorSetLayout(device, &descriptorSetLayoutCreateInfo, NULL, &descriptorSetLayout));
}

void CVulkanComputing::createDescriptorSet() {

    VkDescriptorPoolSize descriptorPoolSize = {};
    descriptorPoolSize.type = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
    descriptorPoolSize.descriptorCount = 1;

    VkDescriptorPoolCreateInfo descriptorPoolCreateInfo = {};
    descriptorPoolCreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    descriptorPoolCreateInfo.maxSets = 1;
    descriptorPoolCreateInfo.poolSizeCount = 1;
    descriptorPoolCreateInfo.pPoolSizes = &descriptorPoolSize;

    VK_CHECK_RESULT(vkCreateDescriptorPool(device, &descriptorPoolCreateInfo, NULL, &descriptorPool));

    VkDescriptorSetAllocateInfo descriptorSetAllocateInfo = {};
    descriptorSetAllocateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    descriptorSetAllocateInfo.descriptorPool = descriptorPool;
    descriptorSetAllocateInfo.descriptorSetCount = 1;
    descriptorSetAllocateInfo.pSetLayouts = &descriptorSetLayout;

    VK_CHECK_RESULT(vkAllocateDescriptorSets(device, &descriptorSetAllocateInfo, &descriptorSet));

    /*
    Next, we need to connect our actual storage buffer with the descrptor.
    We use vkUpdateDescriptorSets() to update the descriptor set.
    */

    // Specify the buffer to bind to the descriptor.
    VkDescriptorBufferInfo descriptorBufferInfo = {};
    descriptorBufferInfo.buffer = buffer;
    descriptorBufferInfo.offset = 0;
    descriptorBufferInfo.range = bufferSize;

    VkWriteDescriptorSet writeDescriptorSet = {};
    writeDescriptorSet.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    writeDescriptorSet.dstSet = descriptorSet;
    writeDescriptorSet.dstBinding = 0;
    writeDescriptorSet.descriptorCount = 1;
    writeDescriptorSet.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
    writeDescriptorSet.pBufferInfo = &descriptorBufferInfo;

    vkUpdateDescriptorSets(device, 1, &writeDescriptorSet, 0, NULL);
}

