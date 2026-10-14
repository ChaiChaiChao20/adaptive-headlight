# Adaptive headlight — ambient light demo

This Wokwi Arduino Uno model samples the photoresistor's analog output and switches one SPDT relay between two indicator branches. Bright surroundings select the red low-beam indicator; darkness selects the green high-beam indicator. Hysteresis switches to high beam at ADC 560 and returns to low beam at ADC 500.

## Run it

Open this folder as a Wokwi Arduino project or create a new Arduino Uno project and paste `sketch.ino` and `diagram.json`. Adjust the photoresistor sensor's `lux` control while the simulation runs. The bundled diagram starts at 400 lux, where Wokwi's default sensor model returns about 281 ADC counts, so the red branch is selected. Lower light raises the analog reading; for example, Wokwi documents about 633 counts at 50 lux and about 511 at 100 lux.

## Wiring map

| Part | Connection |
|---|---|
| Photoresistor VCC/GND/AO | Uno 5V/GND/A0 |
| Relay VCC/GND/IN | Uno 5V/GND/D7 |
| Relay COM | Uno 5V reference supply for the indicator branches |
| Relay NC | 220 Ω resistor → red LED anode; red LED cathode → GND |
| Relay NO | 220 Ω resistor → green LED anode; green LED cathode → GND |

The relay is configured as active-low (`transistor: pnp`): LOW connects COM to NC; HIGH connects COM to NO. The code therefore starts at LOW beam and drives D7 HIGH for the dark/high-beam indicator.

## Boundary

This demonstration switches on ambient light only. It does not detect oncoming traffic, road curvature, pedestrians or glare and must not control a real vehicle headlamp. A road-ready system needs an automotive-rated driver, compliant optics, fail-safe diagnostics and certified validation.

References: [Wokwi relay module behavior](https://docs.wokwi.com/parts/wokwi-relay-module), [Wokwi photoresistor sensor and ADC examples](https://docs.wokwi.com/parts/wokwi-photoresistor-sensor).
