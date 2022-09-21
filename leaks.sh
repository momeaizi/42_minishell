while (true);
do
	VAR=$(leaks minishell | grep " leaks for " | awk '{print $3}')
	if  [ "$VAR" != "0" ];
	then
		leaks minishell
	fi
	sleep 3
done
