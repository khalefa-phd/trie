--create table expr (expr varchar(20), version varchar(50), s1 varchar(10), str varchar(100), k int, q int, alg varchar(10), t double);
create table expr_stat (expr varchar(20), version varchar(50), s1 varchar(10), str varchar(100), k int, q int, alg varchar(10), t double, visited int, maxheap int, maxmap int );

create table summary (expr varchar(20), k int, q int, alg varchar(10), cnt int, runtime double);

.separator ,

.import res.csv expr_stat

insert into summary select expr, k, q, alg, count(*) , avg(t) from expr_stat 
where visited is not null
group by expr, q, k,alg order by expr, k,q;




.headers on
.mode csv
.output summary.csv



select s1.expr, s1.k,s1.q, s1.alg, s2.alg, s3.alg, s1.runtime, s2.runtime, s3.runtime  from summary s1 left outer join  summary s2 on (s1.expr=s2.expr and s1.k=s2.k and s1.q=s2.q) left outer join  summary s3 on  (s2.expr=s3.expr and s2.k=s3.k and  s2.q=s3.q) where  s1.alg>s2.alg and s2.alg >s3.alg;