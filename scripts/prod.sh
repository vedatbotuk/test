#!/bin/bash

# Save the current directory and change to the parent directory
pushd ../ > /dev/null

echo "OTA Build Script for Production Devices"
echo "----------------------------------------"

# Define the CSV file and the settings.conf file
CSV_FILE="scripts/prod_devices.csv"
SETTINGS_FILE="settings.conf"
BACKUP_FILE="scripts/settings.conf.cache"

# Check if the CSV file exists
if [ ! -f "$CSV_FILE" ]; then
  echo "CSV file $CSV_FILE does not exist. Exiting script."
  exit 1
fi

# Check if the settings.conf file exists
if [ ! -f "$SETTINGS_FILE" ]; then
  echo "Settings file $SETTINGS_FILE does not exist. Exiting script."
  exit 1
fi

# Backup the original settings.conf
cp "$SETTINGS_FILE" "$BACKUP_FILE"
echo "Backup of ${SETTINGS_FILE} created as ${BACKUP_FILE}."

# Check if DEV_PROD exists and change it to prod in settings.conf only once
if grep -q "^DEV_PROD=" "$SETTINGS_FILE"; then
    echo "Changing DEV_PROD to prod in settings.conf"
    sed -i "s/^DEV_PROD=.*/DEV_PROD=prod/" "$SETTINGS_FILE"
else
  echo "DEV_PROD key does not exist in settings.conf. Exiting script."
  exit 1
fi

# Source the ESP-IDF environment script
echo "Sourcing the ESP-IDF environment..."
if . "$HOME/esp/esp-idf/export.sh" > /dev/null 2>&1; then
    echo "ESP-IDF environment sourced successfully."
else
    echo "Failed to source ESP-IDF environment. Please check the path and try again."
    exit 1
fi

echo ""
echo "----------------------------------------"
echo "Starting the build process..."
echo "----------------------------------------"
{
  read  # Skip the header line
  while IFS=',' read -r MODEL_ID DEVICE_NAME COMMENT || [ -n "$MODEL_ID" ]; do
      # Remove leading/trailing whitespaces
      MODEL_ID=$(echo "$MODEL_ID" | xargs)

      # Update the settings.conf file with the new MODEL_ID
      echo "Updating settings.conf with MODEL_ID: $MODEL_ID"
      sed -i "s/^MODEL_ID=.*/MODEL_ID=$MODEL_ID/" "$SETTINGS_FILE"

      # Set target for ESP32H2
      idf.py set-target esp32h2 > /dev/null 2>&1
      # Build
      idf.py build > /dev/null 2>&1

      # Clean up
      echo "Removing build directory and related files..."
      idf.py fullclean
      rm -f sdkconfig sdkconfig.old sdkconfig.defaults dependencies.lock || true
      echo "Clean up completed."

      # Indicate completion of the build
      echo "Build completed for MODEL_ID: $MODEL_ID"
      echo "----------------------------------------"
  done
} < "$CSV_FILE"

# Restore the original settings.conf from the backup
mv "$BACKUP_FILE" "$SETTINGS_FILE"
echo ""
echo "settings.conf has been reset to its original state."
echo "Finished building all devices in the CSV file."
echo "OTA Files are in ./ota"
echo "----------------------------------------"
echo "OTA Build Script for Production Devices completed."

# Change back to the original directory
popd > /dev/null