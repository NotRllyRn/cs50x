select title from movies
join stars on movies.id = stars.movie_id
join people on stars.person_id = people.id
where people.name = "Johnny Depp"
and movies.id in
(select id from movies
where id in
(select movie_id from stars
where person_id =
(select id from people
where name = "Helena Bonham Carter")));