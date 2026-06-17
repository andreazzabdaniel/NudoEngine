#pragma once





// Indices (locations) of Queue Familyes (if they exists)
struct QueueFamilyIndices
{
	uint32_t graphicsFamily = -1;			// Location of Graphics Queue Family
	uint32_t presentationFamily = -1;		// Presentation family

	bool isValid()
	{
		return graphicsFamily >= 0 && presentationFamily >= 0;
	}
};