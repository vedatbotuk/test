const fz = require('zigbee-herdsman-converters/converters/fromZigbee');
const tz = require('zigbee-herdsman-converters/converters/toZigbee');
const exposes = require('zigbee-herdsman-converters/lib/exposes');
const reporting = require('zigbee-herdsman-converters/lib/reporting');
const ota = require('zigbee-herdsman-converters/lib/ota');
const e = exposes.presets;


const definition = {
  zigbeeModel: ['56384'], // Model ID as per device's Zigbee data.
  model: 'ESP32H2_Sensor', // Vendor model number for the light device.
  vendor: 'Botuk', // Vendor name (e.g., Philips, IKEA, etc.)
  description: 'Simple on/off light device', // Short description of the device
  fromZigbee: [fz.on_off, fz.temperature, fz.battery], // Handles incoming Zigbee messages for on/off states
  toZigbee: [tz.on_off], // Used to control the light (on/off commands)
  configure: async (device, coordinatorEndpoint, logger) => {
    const endpoint = device.getEndpoint(10); // Endpoint for the light control
    const bindClusters = ['genOnOff', 'msTemperatureMeasurement', 'genPowerCfg'];
    await reporting.temperature(endpoint, { min: 300, max: 65000, change: 200 });
    await reporting.batteryPercentageRemaining(endpoint, { min: 3600, max: 65000, change: 1 });
    await reporting.onOff(endpoint); // Set up reporting for the on/off state
  },
  exposes: [e.switch(), e.temperature(), e.battery()], // Expose the on/off switch for the device
  ota: ota.zigbeeOTA
};

module.exports = definition;