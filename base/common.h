#pragma once

#include <vector>
#include <iostream>
#include <assert.h>
#include <vulkan/vulkan.h>

#define SUCCESS(create_func) \
if(VK_SUCCESS!=create_func) \
std::cout<<"error "<<#create_func<<std::endl;\
else \
std::cout<<"success "<<#create_func<<std::endl;