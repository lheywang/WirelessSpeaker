DTC_EXECNAME := WirelessSpeaker

include ../../Makefile

CC := dtc
FLAGS := -@ -Hepapr -I dts -O dtb -o
SOURCE := WirelessSpeakerV1.dts

# Clean !
dtc_clean:
	@-rm -rf $(DTC_EXECNAME).dtbo

# Compile
dtc_compile: WirelessSpeakerV1.dts
	$(CC) $(FLAGS) $(DTC_EXECNAME).dtbo $(SOURCE)





