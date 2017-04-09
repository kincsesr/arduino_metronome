# arduino_metronome
a simple metronome for an arduino board

## Board type:
- Arduino Uno R3

## Pins:
- Pin 3: press button, enable/disable speaker
- Pin 4: press button, increse tempo
- Pin 5: press button, decrease tempo

- Pin 8: speaker

- Pin 9: (blue) LED, turned on when tempo increased
- Pin 10: (yellow) LED, turned on when tempo decreased

- Pin 11: (green) LED, shows rythm 
- Pin 12: (red) LED, shows first beat

## Serial logging
Serial logging should be commented out as it uses
too much cycles and makes the metronome rather
inaccurate.