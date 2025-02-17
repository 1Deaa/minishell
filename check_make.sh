# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    check_make.sh                                      :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: drahwanj <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/17 16:09:17 by drahwanj          #+#    #+#              #
#    Updated: 2025/02/17 16:09:18 by drahwanj         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

# Run make command
make

# Check if make succeeded
if [ $? -ne 0 ]; then
    echo "Make failed. Exiting with error code."
    exit 1
else
    echo "Make succeeded."
    exit 0
fi
