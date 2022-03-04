# indexing-movies
Creating binary search tree format according to movie title from txt file with

Create date:10/2019 
Author: Berk Limoncu


In this project, you are given a list of movies in an external text file called “movies.txt”. In this text file, you can find a number of real movies extracted from the open movie database1.
This file includes the following information: Title: title of the movie
Year: year of the movie
imdbID: ID of the movie for the IMBD
PosterLink: Link to visualize the poster of the movie
And sample data is as follows where each part is separated by a "," character: Title,Year,imdbID,PosterLink
Saw,2004,tt0387564,https://m.mediaamazon.com/images/M/MV5BMjE4MDYzNDE1OV5BMl 5BanBnXkFtZTcwNDY2OTYwNA@@._V1_SX300.jpg
Love Actually,2003,tt0314331,https://m.mediaamazon.com/images /M/MV5BMTY4NjQ5NDc0Nl5BMl5BanBnXkFtZTYwNjk5NDM3._V1_SX300.jpg

Project task's here is to process this file, and generate an AVL tree based on the movie title. If there is more than one movie with the same title, they should then be stored together in the same node.



<h2>Functional Requirements</h2>

1) Display the full index: This will display the full AVL tree constructed. For traversal, you need to display the movies alphabetically sorted based on their titles.
2) Display the movies where their title contains a specific keyword: This will display the details of the movies (Title, Year, imdbID, and PosterLink) that contains the specified keyword in their title. For example if the search keyword is “Saw”, then based on the above list, it should display following;
Saw,2004,tt0387564,https://m.mediaamazon.com/images/M/MV5BMjE4MDYzNDE1OV 5BMl5BanBnXkFtZTcwNDY2OTYwNA@@._V1_SX300.jpg
Saw IV,2007,tt0890870,https://m.mediaamazon.com/images/M/ MV5BNjc0NjUyNzg3MF5BMl5BanBnXkFtZTYwODMxOTM3._V1_SX300.jpg
Please note that if the movie has more than one release, they should also be displayed
here.

3) The year with the maximum number of movies: This will display the details (Title, Year,
imdbID, and PosterLink) of the movies within the year which has maximum number of movies




<h2>Sample Run</h2>

<img width="509" alt="image" src="https://user-images.githubusercontent.com/76854271/156812791-eb83fc76-a737-4b82-8e85-c271d583e856.png">

<img width="478" alt="image" src="https://user-images.githubusercontent.com/76854271/156812848-97fac0b0-4305-4ca7-b8c6-a9b854d30ac7.png">

<img width="498" alt="image" src="https://user-images.githubusercontent.com/76854271/156812885-2beb6afe-fe51-48ac-8220-3bf5c1e7a579.png">



