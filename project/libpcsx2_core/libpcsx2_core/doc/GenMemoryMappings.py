# -*- coding: utf-8 -*-
"""
Generates a CSV file containing the memory mappings implemented in Resoures/Resources_t.cpp.
This is done by looking at any call made to:
    MMU_OBJECT_CATEGORY->MMU->mapObject(ADDRESS, MAPPED_OBJECT); .
    
Output Format:
    Object Category/Name    {X} MMU Address    {Y} MMU Address    {Z} MMU Address
"""

import re
import csv

resourcesFile = "../src/Resources/Resources_t.cpp"
csvFile = "MemoryMappings.csv"
regexString = r"(?:.*->)?(.*)->MMU->mapObject\((0x[a-fA-F0-9]{1,8}).*,\s+([^\)]*)\)+;"
mapStrings = []

# Find mapObject lines.
with open(resourcesFile) as f:
    for line in f:
        searchLine = re.search(r"mapObject\(", line)
        if searchLine is not None:
            mapStrings.append(line.strip())

# Extract the MMU_OBJECT_CATEGORY (group 1), ADDRESS (group2), 
#  and MAPPED_OBJECT (group 3) for each line, and store in a dictonary.
mapInfo = {}
mmuContexts = []
for entry in mapStrings:
    # Search for regex.
    result = re.search(regexString, entry)
    
    # Add header (MMU context) if it doesnt already exist to list of CSV headers.
    if result.group(1) not in mmuContexts:
        mmuContexts.append(result.group(1))
    
    # Extract Info.
    if result.group(3) in mapInfo:
        mapInfo[result.group(3)][result.group(1)] = int(result.group(2), 16)
    else:
        mapInfo[result.group(3)] = { result.group(1) : int(result.group(2), 16) }
        
# Sort the MMU contexts by alphabetical order.
mmuContexts.sort()

# Write to csv file.
with open(csvFile, "w", newline='') as f:
    w = csv.writer(f)
    w.writerow(["Mapped Object", "MMU Mapped Address (hex)"])
    w.writerow([""] + mmuContexts)
    w.writerow([])
    for mappedObject, mmuMapInfo in mapInfo.items():
        # Construct the information in the order as described at the start.
        row = [mappedObject]
        for mmuContext in mmuContexts:
            if mmuContext in mmuMapInfo:
                row.append('0x{0:08X}'.format(mmuMapInfo[mmuContext]))
            else:
                row.append("")
        
        # Write the object information.
        w.writerow(row)
