#!/bin/bash

# Pokemon ROM Hack Town Renaming Script
# This script renames all references from old town names to new ones

set -e  # Exit on any error

echo "=== Pokemon Town Renaming Script ==="
echo "This will rename:"
echo "  OldaleTown -> OldScumport"
echo "  LittlerootTown -> Trashburg"  
echo "  PetalburgCity -> GiantsReach"
echo "  PetalburgWoods -> ScrappleHollow"
echo "  RustboroCity -> WawaPark"
echo ""

# Backup the current state
echo "Creating backup..."
git add -A 2>/dev/null || true
git commit -m "Backup before town renaming" 2>/dev/null || echo "No changes to commit"

echo "Starting renaming process..."

# Step 1: Fix the directory names that were already renamed incorrectly
echo "Step 1: Fixing directory names..."
cd data/maps

# Fix RustboroCity -> WawaPark (not WawaParkCity)
for dir in WawaParkCity*; do
    if [ -d "$dir" ]; then
        new_name=$(echo "$dir" | sed 's/WawaParkCity/WawaPark/g')
        echo "  Renaming $dir -> $new_name"
        mv "$dir" "$new_name"
    fi
done

# Fix GiantsReachCity -> GiantsReach
for dir in GiantsReachCity*; do
    if [ -d "$dir" ]; then
        new_name=$(echo "$dir" | sed 's/GiantsReachCity/GiantsReach/g')
        echo "  Renaming $dir -> $new_name"
        mv "$dir" "$new_name"
    fi
done

cd ../..

# Step 2: Update map_groups.json
echo "Step 2: Updating map_groups.json..."

# Update group order
sed -i 's/"gMapGroup_IndoorLittleroot"/"gMapGroup_IndoorTrashburg"/g' data/maps/map_groups.json
sed -i 's/"gMapGroup_IndoorOldale"/"gMapGroup_IndoorOldScumport"/g' data/maps/map_groups.json
sed -i 's/"gMapGroup_IndoorPetalburg"/"gMapGroup_IndoorGiantsReach"/g' data/maps/map_groups.json
sed -i 's/"gMapGroup_IndoorRustboro"/"gMapGroup_IndoorWawaPark"/g' data/maps/map_groups.json

# Update town names in main group
sed -i 's/"PetalburgCity"/"GiantsReach"/g' data/maps/map_groups.json
sed -i 's/"RustboroCity"/"WawaPark"/g' data/maps/map_groups.json
sed -i 's/"LittlerootTown"/"Trashburg"/g' data/maps/map_groups.json
sed -i 's/"OldaleTown"/"OldScumport"/g' data/maps/map_groups.json

# Update map names in indoor groups
sed -i 's/"LittlerootTown_/"Trashburg_/g' data/maps/map_groups.json
sed -i 's/"OldaleTown_/"OldScumport_/g' data/maps/map_groups.json
sed -i 's/"PetalburgCity_/"GiantsReach_/g' data/maps/map_groups.json
sed -i 's/"RustboroCity_/"WawaPark_/g' data/maps/map_groups.json

# Update group names in group definitions
sed -i 's/"gMapGroup_IndoorLittleroot":/"gMapGroup_IndoorTrashburg":/g' data/maps/map_groups.json
sed -i 's/"gMapGroup_IndoorOldale":/"gMapGroup_IndoorOldScumport":/g' data/maps/map_groups.json
sed -i 's/"gMapGroup_IndoorPetalburg":/"gMapGroup_IndoorGiantsReach":/g' data/maps/map_groups.json
sed -i 's/"gMapGroup_IndoorRustboro":/"gMapGroup_IndoorWawaPark":/g' data/maps/map_groups.json

# Step 3: Update all map.json files in renamed directories
echo "Step 3: Updating map.json files..."
find data/maps -name "map.json" -type f | while read file; do
    echo "  Updating $file"
    sed -i 's/"LittlerootTown_/"Trashburg_/g' "$file"
    sed -i 's/"OldaleTown_/"OldScumport_/g' "$file"
    sed -i 's/"PetalburgCity_/"GiantsReach_/g' "$file"
    sed -i 's/"PetalburgWoods"/"ScrappleHollow"/g' "$file"
    sed -i 's/"RustboroCity_/"WawaPark_/g' "$file"
done

# Step 4: Update all script files
echo "Step 4: Updating script files..."
find . -name "*.inc" -type f | while read file; do
    echo "  Updating $file"
    # Update script names and references
    sed -i 's/LittlerootTown_/Trashburg_/g' "$file"
    sed -i 's/OldaleTown_/OldScumport_/g' "$file"
    sed -i 's/PetalburgCity_/GiantsReach_/g' "$file"
    sed -i 's/PetalburgWoods/ScrappleHollow/g' "$file"
    sed -i 's/RustboroCity_/WawaPark_/g' "$file"
    
    # Update map names in comments and references
    sed -i 's/LittlerootTown/Trashburg/g' "$file"
    sed -i 's/OldaleTown/OldScumport/g' "$file"
    sed -i 's/PetalburgCity/GiantsReach/g' "$file"
    sed -i 's/RustboroCity/WawaPark/g' "$file"
done

# Step 5: Update constants and flags
echo "Step 5: Updating constants and flags..."
find . -name "*.h" -type f | while read file; do
    echo "  Updating $file"
    # Update flag names
    sed -i 's/FLAG_LITTLEROOT/FLAG_TRASHBURG/g' "$file"
    sed -i 's/FLAG_OLDALE/FLAG_OLD_SCUMPORT/g' "$file"
    sed -i 's/FLAG_PETALBURG/FLAG_GIANTS_REACH/g' "$file"
    sed -i 's/FLAG_RUSTBORO/FLAG_WAWA_PARK/g' "$file"
    
    # Update variable names
    sed -i 's/VAR_LITTLEROOT/VAR_TRASHBURG/g' "$file"
    sed -i 's/VAR_OLDALE/VAR_OLD_SCUMPORT/g' "$file"
    sed -i 's/VAR_PETALBURG/VAR_GIANTS_REACH/g' "$file"
    sed -i 's/VAR_RUSTBORO/VAR_WAWA_PARK/g' "$file"
    
    # Update location constants
    sed -i 's/HEAL_LOCATION_LITTLEROOT_TOWN/HEAL_LOCATION_TRASHBURG/g' "$file"
    sed -i 's/HEAL_LOCATION_OLDALE_TOWN/HEAL_LOCATION_OLD_SCUMPORT/g' "$file"
    sed -i 's/HEAL_LOCATION_PETALBURG_CITY/HEAL_LOCATION_GIANTS_REACH/g' "$file"
    sed -i 's/HEAL_LOCATION_RUSTBORO_CITY/HEAL_LOCATION_WAWA_PARK/g' "$file"
done

# Step 6: Update source files
echo "Step 6: Updating source files..."
find src -name "*.c" -type f | while read file; do
    echo "  Updating $file"
    sed -i 's/LittlerootTown/Trashburg/g' "$file"
    sed -i 's/OldaleTown/OldScumport/g' "$file"
    sed -i 's/PetalburgCity/GiantsReach/g' "$file"
    sed -i 's/PetalburgWoods/ScrappleHollow/g' "$file"
    sed -i 's/RustboroCity/WawaPark/g' "$file"
done

# Step 7: Update any remaining references
echo "Step 7: Updating remaining references..."
find . -name "*.mk" -o -name "Makefile" -o -name "*.ld" | while read file; do
    echo "  Updating $file"
    sed -i 's/LittlerootTown/Trashburg/g' "$file"
    sed -i 's/OldaleTown/OldScumport/g' "$file"
    sed -i 's/PetalburgCity/GiantsReach/g' "$file"
    sed -i 's/PetalburgWoods/ScrappleHollow/g' "$file"
    sed -i 's/RustboroCity/WawaPark/g' "$file"
done

echo "Step 8: Regenerating auto-generated files..."
# The build system will regenerate these files when we compile
rm -f data/maps/groups.inc 2>/dev/null || true
rm -f data/maps/headers.inc 2>/dev/null || true

echo ""
echo "=== Renaming Complete! ==="
echo ""
echo "Summary of changes:"
echo "  - Map directories renamed"
echo "  - map_groups.json updated"
echo "  - All script files updated"
echo "  - Constants and flags updated"
echo "  - Source files updated"
echo ""
echo "Next steps:"
echo "1. Test compile with: make"
echo "2. Check for any remaining references: grep -r 'OldaleTown\\|LittlerootTown\\|PetalburgCity\\|RustboroCity' . --exclude-dir=.git"
echo "3. Commit changes: git add -A && git commit -m 'Renamed all towns to new names'"
echo ""