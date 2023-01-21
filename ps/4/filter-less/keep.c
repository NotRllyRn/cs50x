for (int i = r - 1; i < r + 1; i++)
            {
                for (int j = c - 1; j < c + 1; j++)
                {
                    if ((i < 0) || (i >= height) || (j < 0) || (j >= width))
                    {
                        continue;
                    }

                    // calculates the gx values
                    if (i == r + 1 || i == r - 1)
                    {
                        if (j == c - 1)
                        {
                            Gx[0] += (-copy[i][j].rgbtRed);
                            Gx[1] += (-copy[i][j].rgbtGreen);
                            Gx[2] += (-copy[i][j].rgbtBlue);
                        }
                        else if (j == c + 1)
                        {
                            Gx[0] += (copy[i][j].rgbtRed);
                            Gx[1] += (copy[i][j].rgbtGreen);
                            Gx[2] += (copy[i][j].rgbtBlue);
                        }
                    }
                    else
                    {
                        if (j == c - 1)
                        {
                            Gx[0] += (copy[i][j].rgbtRed) * -2;
                            Gx[1] += (copy[i][j].rgbtGreen) * -2;
                            Gx[2] += (copy[i][j].rgbtBlue) * -2;
                        }
                        else if (j == c + 1)
                        {
                            Gx[0] += (copy[i][j].rgbtRed) * 2;
                            Gx[1] += (copy[i][j].rgbtGreen) * 2;
                            Gx[2] += (copy[i][j].rgbtBlue) * 2;
                        }
                    }

                    // calculate the values for Gy
                    if (j == c + 1 || j == c - 1)
                    {
                        if (i == r - 1)
                        {
                            Gy[0] += (-copy[i][j].rgbtRed);
                            Gy[1] += (-copy[i][j].rgbtGreen);
                            Gy[2] += (-copy[i][j].rgbtBlue);
                        }
                        else if (i == r + 1)
                        {
                            Gy[0] += (copy[i][j].rgbtRed);
                            Gy[1] += (copy[i][j].rgbtGreen);
                            Gy[2] += (copy[i][j].rgbtBlue);
                        }
                    }
                    else
                    {
                        if (i == r - 1)
                        {
                            Gy[0] += (copy[i][j].rgbtRed) * -2;
                            Gy[1] += (copy[i][j].rgbtGreen) * -2;
                            Gy[2] += (copy[i][j].rgbtBlue) * -2;
                        }
                        else if (i == r + 1)
                        {
                            Gy[0] += (copy[i][j].rgbtRed) * 2;
                            Gy[1] += (copy[i][j].rgbtGreen) * 2;
                            Gy[2] += (copy[i][j].rgbtBlue) * 2;
                        }
                    }
                }
            }