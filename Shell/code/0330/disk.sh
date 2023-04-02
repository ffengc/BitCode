# Custom DJRavine Modification
# login_pwd='pwd';
# login_date='date';
# login_users='users';
# login_uptime='uptime';
# server_ip='/sbin/ifconfig | grep 'inet addr:'| grep -v '127.0.0.1' | head -1 | cut -d: -f2 | awk '{ print $1}'';
disk_available=$(df -h --block-size=1024 | awk '{sum += $4;} END {print sum;}');
disk_used=$(df -lh --block-size=1024 | awk '{sum += $3;} END {print sum;}');
disk_size=$(df -lh --block-size=1024 | awk '{sum += $2;} END {print sum;}');
disk_available_gb=$(echo "scale=2; $disk_available/(1024^2)" | bc)
disk_used_gb=$(echo "scale=2; $disk_used/(1024^2)" | bc)
disk_size_gb=$(echo "scale=2; $disk_size/(1024^2)" | bc)

red="\033[31m"
blue="\033[34m"
green="\033[32m"

echo -e " "
echo -e "$+-----------------------------------------"
# du -lh | column -c 6 | awk '{ printf " \033[22;32m%s\t%s\t\033[22;31m%s\t%s\t%s\n", $1, $6, $2, $3, $4, $5}'
echo -e "Total Disk Space: ${disk_size_gb} GB"
echo -e "Total Free Space: ${disk_available_gb} GB"
echo -e "Total Used Space: ${disk_used_gb} GB"
echo -e "+-----------------------------------------"
