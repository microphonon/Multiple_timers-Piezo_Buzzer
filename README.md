# Piezo_Buzzer

Use the MSP430FR5969 Launchpad to play a repetitive two-tone sequence through an external piezoelectric buzzer. Square waves are generated at 2200 and 1300 Hz, which are the maritime radiotelephone distress frequencies. Tone duration is set by timer TA0 sourced to the VLO clock at 10 kHz. Tone frequency is set by TA1 sourced to SMCLK at 500 kHz. Drive the buzzer with TA1.1 output on P1.2. Use the TA0 interrupt to change the frequency.
