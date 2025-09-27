#!/bin/bash

# Script to update variable and constant references after town renaming

echo "Updating variable and constant references..."

# Create mapping of old to new variable names
declare -A var_mappings=(
    ["VAR_LITTLEROOT_TOWN_STATE"]="VAR_TRASHBURG_STATE"
    ["VAR_LITTLEROOT_INTRO_STATE"]="VAR_TRASHBURG_INTRO_STATE" 
    ["VAR_LITTLEROOT_HOUSES_STATE_MAY"]="VAR_TRASHBURG_HOUSES_STATE_MAY"
    ["VAR_LITTLEROOT_HOUSES_STATE_BRENDAN"]="VAR_TRASHBURG_HOUSES_STATE_BRENDAN"
    ["VAR_LITTLEROOT_RIVAL_STATE"]="VAR_TRASHBURG_RIVAL_STATE"
    ["VAR_OLDALE_TOWN_STATE"]="VAR_OLD_SCUMPORT_TOWN_STATE"
    ["VAR_OLDALE_RIVAL_STATE"]="VAR_OLD_SCUMPORT_RIVAL_STATE"
    ["VAR_PETALBURG_CITY_STATE"]="VAR_GIANTS_REACH_CITY_STATE"
    ["VAR_PETALBURG_GYM_STATE"]="VAR_GIANTS_REACH_GYM_STATE"
    ["VAR_PETALBURG_WOODS_STATE"]="VAR_GIANTS_REACH_WOODS_STATE"
    ["VAR_RUSTBORO_CITY_STATE"]="VAR_WAWA_PARK_CITY_STATE"
)

# Create mapping of old to new heal location constants
declare -A heal_mappings=(
    ["HEAL_LOCATION_LITTLEROOT_TOWN"]="HEAL_LOCATION_TRASHBURG"
    ["HEAL_LOCATION_LITTLEROOT_TOWN_BRENDANS_HOUSE_2F"]="HEAL_LOCATION_TRASHBURG_BRENDANS_HOUSE_2F"
    ["HEAL_LOCATION_LITTLEROOT_TOWN_MAYS_HOUSE_2F"]="HEAL_LOCATION_TRASHBURG_MAYS_HOUSE_2F"
    ["HEAL_LOCATION_OLDALE_TOWN"]="HEAL_LOCATION_OLD_SCUMPORT"
    ["HEAL_LOCATION_PETALBURG_CITY"]="HEAL_LOCATION_GIANTS_REACH"
    ["HEAL_LOCATION_RUSTBORO_CITY"]="HEAL_LOCATION_WAWA_PARK"
)

# Create mapping of old to new flag constants
declare -A flag_mappings=(
    ["FLAG_PETALBURG_CITY_CAN_SEARCH_BUSHES"]="FLAG_GIANTS_REACH_CITY_CAN_SEARCH_BUSHES"
    ["FLAG_PETALBURG_NURSE_INTRO_DONE"]="FLAG_GIANTS_REACH_NURSE_INTRO_DONE"
    ["FLAG_PETALBURG_MART_EXPANDED_ITEMS"]="FLAG_GIANTS_REACH_MART_EXPANDED_ITEMS"
    ["FLAG_OLDALE_NURSE_INTRO_DONE"]="FLAG_OLD_SCUMPORT_NURSE_INTRO_DONE"
    ["FLAG_RUSTBORO_NPC_TRADE_COMPLETED"]="FLAG_WAWA_PARK_NPC_TRADE_COMPLETED"
)

# Function to update variables in files
update_variables() {
    local file_pattern="$1"
    
    echo "Updating variables in $file_pattern files..."
    
    for old_var in "${!var_mappings[@]}"; do
        new_var="${var_mappings[$old_var]}"
        echo "  $old_var -> $new_var"
        find . -name "$file_pattern" -type f -exec sed -i "s/${old_var}/${new_var}/g" {} \;
    done
    
    for old_heal in "${!heal_mappings[@]}"; do
        new_heal="${heal_mappings[$old_heal]}"
        echo "  $old_heal -> $new_heal"
        find . -name "$file_pattern" -type f -exec sed -i "s/${old_heal}/${new_heal}/g" {} \;
    done
    
    for old_flag in "${!flag_mappings[@]}"; do
        new_flag="${flag_mappings[$old_flag]}"
        echo "  $old_flag -> $new_flag" 
        find . -name "$file_pattern" -type f -exec sed -i "s/${old_flag}/${new_flag}/g" {} \;
    done
}

# Update script files
update_variables "*.inc"
update_variables "*.s"

echo "Variable and constant updates complete!"
echo "You should now update the constants definitions to match the new names."