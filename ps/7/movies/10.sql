select distinct name from movies
join directors on movies.id = directors.movie_id
join people on directors.person_id = people.id
join ratings on movies.id = ratings.movie_id
where rating >= 9;