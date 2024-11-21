const fz = require('zigbee-herdsman-converters/converters/fromZigbee');
const tz = require('zigbee-herdsman-converters/converters/toZigbee');
const exposes = require('zigbee-herdsman-converters/lib/exposes');
const reporting = require('zigbee-herdsman-converters/lib/reporting');
const ota = require('zigbee-herdsman-converters/lib/ota');
const e = exposes.presets;

const definition = {
  zigbeeModel: ['64512'],
  model: '64512',
  vendor: 'Botuk',
  description: 'Temp/Hum Sensor',
  fromZigbee: [fz.on_off, fz.temperature, fz.battery],
  toZigbee: [tz.on_off],
  configure: async (device, coordinatorEndpoint, logger) => {
    const endpoint = device.getEndpoint(10);
    const bindClusters = ['msTemperatureMeasurement', 'msHumidityMeasurement', 'genPowerCfg'];

    // Bind clusters to ensure proper reporting
    await device.bind(endpoint, coordinatorEndpoint, bindClusters);

    // Configure reporting for temperature, humidity, battery
    await reporting.temperature(endpoint, { min: 300, max: 3600, change: 100 });
    await reporting.humidity(endpoint, { min: 300, max: 3600, change: 100 });
    await reporting.batteryPercentageRemaining(endpoint, { min: 3600, max: 65000, change: 1 });
  },
  exposes: [e.temperature(), e.humidity(), e.battery()],
  ota: ota.zigbeeOTA
};

module.exports = definition;
