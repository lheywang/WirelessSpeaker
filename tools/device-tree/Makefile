DTC_EXECNAME := WirelessSpeaker

include ../../Makefile

CC := dtc
FLAGS := -@ -Hepapr -I dts -O dtb -o
SOURCE := WirelessSpeakerV1.dts

# Clean !
dtc_clean:
	@rm -r $(DTC_EXECNAME)

# Compile
dtc_compile: WirelessSpeakerV1.dts
	$(CC) $(FLAGS) $(DTC_EXECNAME).dtb $(SOURCE)

# Compile and deploy the device tree.
dtc_deploy: dtc_compile
	@scp -i $(KEY) $(DTC_EXECNAME).dtb pi@$(RPI):/firmware/overlays/$(DTC_EXECNAME).dtb
# Now we had to add it to the config.txt !

# Compile and load dynamically. Doesn't install anything.
dtc_test: dtc_compile
	@scp -i $(KEY) $(DTC_EXECNAME).dtb pi@$(RPI):/firmware/overlays/$(DTC_EXECNAME).dtb
	@ssh -i &(KEY) pi@$(RPI) -f "sudo dtoverlay $(DTC_EXECNAME).dtb" 



