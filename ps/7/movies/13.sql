select distinct name from movies
join stars on movies.id = stars.movie_id
join people on stars.person_id = people.id
where movies.id in
(select id from movies
where id in
(select movie_id from stars
where person_id in
(select id from people
where name = "Kevin Bacon")))
and not people.name = "Kevin Bacon"
limit 50;