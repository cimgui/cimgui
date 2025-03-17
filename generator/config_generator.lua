return {
	vulkan = {(os.getenv("VULKAN_SDK") or "vulkan_SDK_not_found").."/Include"}, --{[[C:\VulkanSDK\1.3.216.0\Include]]}
	sdlgpu3 = {(os.getenv("SDL_PATH") or "SDL_not_found").."/include"},
}

