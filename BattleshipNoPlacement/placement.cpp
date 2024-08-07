	//Placing comp ships	
	spot = 0;
	for (int i = 0; i < 5; i++)
	{
		int numSpots;
		int letter_row;
		int number_column;
		int direction;

		if (i == 0) { numSpots = 5; }
		if (i == 1) { numSpots = 4; }
		if (i == 2) { numSpots = 3; }
		if (i == 3) { numSpots = 3; }
		if (i == 4) { numSpots = 2; }

		PLACE2: letter_row = rand() % 10;
		number_column = rand() % 10;
		direction = rand() % 2;

		int choices = 0;
		Boolean invalid = FALSE;
		for (int p = 0; p < numSpots; p++)
		{
			if (direction == 0) //right
			{
				if (comp_ship_grid_color[letter_row][number_column + p] == 32)
				{
					invalid = TRUE;
				}
				if (number_column + numSpots > NUMBERS_AXIS)
				{
					invalid = TRUE;
				}
			}
			else //left
			{
				if (comp_ship_grid_color[letter_row + p][number_column] == 32)
				{
					invalid = TRUE;
				}
				if (letter_row + numSpots > LETTERS_AXIS)
				{
					invalid = TRUE;
				}
			}
		}

		while (invalid == TRUE)
		{
			if (choices == 2)
			{
				goto PLACE2;
			}

			invalid = FALSE;
			for (int p = 0; p < numSpots; p++)
			{
				if (direction == 0)
				{
					if (comp_ship_grid_color[letter_row][number_column + p] == 32)
					{
						invalid = TRUE;
					}
					if (number_column + numSpots > NUMBERS_AXIS)
					{
						invalid = TRUE;
					}
				}
				else
				{
					if (comp_ship_grid_color[letter_row + p][number_column] == 32)
					{
						invalid = TRUE;
					}
					if (letter_row + numSpots > LETTERS_AXIS)
					{
						invalid = TRUE;
					}
				}
			}
			choices++;
		}

		if (direction == 0) //places ship
		{
			for (int l = 0; l < numSpots; l++)
			{
				comp_ship_grid_color[letter_row][number_column + l] = 32; 
				comp_total_ship_spots[spot] = (letter_row * LETTERS_AXIS) + (number_column + l);
				spot++;
			}

		}
		else //places ship
		{
			for (int l = 0; l < numSpots; l++)
			{
				comp_ship_grid_color[letter_row + l][number_column] = 32;
				comp_total_ship_spots[spot] = ((letter_row + l) * LETTERS_AXIS) + (number_column);
				spot++;
			}
		}
	}