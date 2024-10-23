sudo cp 60-mystic-light.rules /etc/udev/rules.d/
sudo udevadm control --reload-rules
sudo udevadm trigger
