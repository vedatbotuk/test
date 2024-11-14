// This external converter should be tested.
const ota = require('zigbee-herdsman-converters/lib/ota');

const definition = {
  zigbeeModel: ['50176'], // The model ID from: Device with modelID 'lumi.sens' is not supported.
  model: 'ESP32H2_Sensor', // Vendor model number, look on the device for a model number
  vendor: 'Botuk', // Vendor of the device (only used for documentation and startup logging)
  description: 'test device', // Description of the device, copy from vendor site. (only used for documentation and startup logging)
  configure: async (device, coordinatorEndpoint, logger) => {
    const endpoint = device.getEndpoint(10);
  },
  ota: ota.zigbeeOTA,
};

module.exports = definition;
