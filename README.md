# Piezo_Buzzer

Use the MSP430FR5969 Launchpad to play a repetitive two-tone sequence through an external piezoelectric buzzer. Square waves are generated at 2200 and 1300 Hz, which are the maritime radiotelephone audio distress frequencies. Tone duration is set by timer TA0 sourced to the VLO clock at 10 kHz. Tone frequency is set by TA1 sourced to SMCLK at 500 kHz. Drive the buzzer with TA1.1 output on P1.2. Use the TA0 interrupt to change the frequency.

A multi-tone piezo buzzer generates a high-quality audio alarm. It is an alternative to signaling with a more expensive electromagnetic buzzer that produces a single audio frequency, typically around 2500 Hz. About 10x more current is required, which may be undesirable in battery applications. In addition, there is a turn-on transient that may cause a noticeable "squeaking" sound: The magnetic buzzer alarm is often heard when a truck or delivery van is in reverse gear.  Advantages of a magnetic buzzer are: i) implemented by simply toggling a GPIO pin and ii) louder.

A simple driver circuit for the piezo-buzzer is shown. It is important to leave TA1.1 in the low state to keep the transistor turned off.

![Driver circuit](https://raw.githubusercontent.com/microphonon/Piezo_Buzzer/master/C1.jpg)
