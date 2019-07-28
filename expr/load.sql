create table expr (expr varchar(20), version varchar(50), str varchar(100), k int, q int, alg varchar(10), t double);
--create table summary (expr varchar(20), k int, q int, meta double, depth double);

.separator ,

.import auth_1dim.csv expr

--insert into summary select expr, k,q, avg(meta), avg(depth) from expr group by expr, q, k;
-- select s1.k, s1.q, s1.meta, s1.depth, s2.meta, s2.depth, s3.meta, s3.depth from summary s1, summary s2, summary  s3
-- where s1.q=s2.q and s1.q=s3.q and s1.k =s2.k and s1.k=s3.k and s1.expr='m1dimo.cc' and s2.expr='m1dim.cc'
-- and s3.expr='m1dim_free.cc'

--.headers on
--.mode csv
--.output summary.csv


--select s1.q, s1.k, s1.meta, s1.depth,s2.meta, s2.depth from summary s1, summary s2 where s1.expr='1dimv0.cc' and s2.expr='m1dimo.cc' and s1.q=s2.q and s1.k=s2.k;


--.output summary.csv
--select * from summary;
