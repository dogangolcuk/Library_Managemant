--
-- PostgreSQL database dump
--

-- Started on 2008-07-27 19:02:51 EEST

SET client_encoding = 'SQL_ASCII';
SET check_function_bodies = false;
SET client_min_messages = warning;

--
-- TOC entry 1633 (class 0 OID 0)
-- Dependencies: 5
-- Name: SCHEMA public; Type: COMMENT; Schema: -; Owner: postgres
--

COMMENT ON SCHEMA public IS 'Standard public schema';


SET search_path = public, pg_catalog;

--
-- TOC entry 210 (class 1247 OID 17630)
-- Dependencies: 5
-- Name: ek_bilgi; Type: DOMAIN; Schema: public; Owner: kutya
--

CREATE DOMAIN ek_bilgi AS text;


ALTER DOMAIN public.ek_bilgi OWNER TO kutya;

--
-- TOC entry 211 (class 1247 OID 17631)
-- Dependencies: 5
-- Name: isim; Type: DOMAIN; Schema: public; Owner: kutya
--

CREATE DOMAIN isim AS character varying(50) NOT NULL;


ALTER DOMAIN public.isim OWNER TO kutya;

SET default_tablespace = '';

SET default_with_oids = true;

--
-- TOC entry 1214 (class 1259 OID 17634)
-- Dependencies: 210 5
-- Name: kitapkategori; Type: TABLE; Schema: public; Owner: kutya; Tablespace: 
--

CREATE TABLE kitapkategori (
    id serial NOT NULL,
    ad character varying(25) NOT NULL,
    ek ek_bilgi
);


ALTER TABLE public.kitapkategori OWNER TO kutya;

--
-- TOC entry 1216 (class 1259 OID 17642)
-- Dependencies: 1563 1564 1565 1566 1567 1568 211 5
-- Name: kitaplar; Type: TABLE; Schema: public; Owner: kutya; Tablespace: 
--

CREATE TABLE kitaplar (
    id serial NOT NULL,
    ad isim,
    isbn character(13),
    barkod character varying(15),
    yayin_tarihi date DEFAULT now(),
    adet smallint DEFAULT (1)::smallint,
    raf character varying(15),
    baski_sayisi smallint,
    giris_tarihi date DEFAULT now(),
    ek text,
    yayinci integer DEFAULT 0,
    giris_sekli integer DEFAULT 0,
    kategori integer DEFAULT 0
);


ALTER TABLE public.kitaplar OWNER TO kutya;

--
-- TOC entry 1220 (class 1259 OID 17660)
-- Dependencies: 1571 1572 5
-- Name: odunc_al_ver; Type: TABLE; Schema: public; Owner: kutya; Tablespace: 
--

CREATE TABLE odunc_al_ver (
    uye_id serial NOT NULL,
    kitap_id serial NOT NULL,
    verme_tarihi date DEFAULT now() NOT NULL,
    alma_tarihi date,
    verdi_vermedi boolean DEFAULT false,
    id serial NOT NULL
);


ALTER TABLE public.odunc_al_ver OWNER TO kutya;

--
-- TOC entry 1222 (class 1259 OID 17669)
-- Dependencies: 211 210 5
-- Name: yayinevi; Type: TABLE; Schema: public; Owner: kutya; Tablespace: 
--

CREATE TABLE yayinevi (
    id serial NOT NULL,
    ad isim,
    ek ek_bilgi
);


ALTER TABLE public.yayinevi OWNER TO kutya;

--
-- TOC entry 1223 (class 1259 OID 17675)
-- Dependencies: 1302 211 211 5
-- Name: encokokunan; Type: VIEW; Schema: public; Owner: kutya
--

CREATE VIEW encokokunan AS
    SELECT k.ad, kk.ad AS kategori, y.ad AS yayinevi, count(*) AS alinma_sayisi FROM kitaplar k, odunc_al_ver o, yayinevi y, kitapkategori kk WHERE (((k.id = o.kitap_id) AND (k.yayinci = y.id)) AND (k.kategori = kk.id)) GROUP BY k.ad, kk.ad, y.ad ORDER BY count(*) DESC;


ALTER TABLE public.encokokunan OWNER TO kutya;

--
-- TOC entry 1225 (class 1259 OID 17680)
-- Dependencies: 1576 1577 211 211 210 5
-- Name: uyeler; Type: TABLE; Schema: public; Owner: kutya; Tablespace: 
--

CREATE TABLE uyeler (
    id serial NOT NULL,
    uye_no character varying(40),
    ad isim,
    soyad isim,
    uyelik_tarihi date DEFAULT now(),
    uyelik_tipi character varying(25),
    tel character(15),
    ceptel character(15),
    email character varying(50),
    adres character varying(250),
    ek_bilgi ek_bilgi,
    sinif integer DEFAULT 0
);


ALTER TABLE public.uyeler OWNER TO kutya;

--
-- TOC entry 1226 (class 1259 OID 17688)
-- Dependencies: 1303 211 211 5
-- Name: encokokuyan; Type: VIEW; Schema: public; Owner: kutya
--

CREATE VIEW encokokuyan AS
    SELECT u.uye_no, u.ad, u.soyad, u.uyelik_tarihi, count(*) AS kitap_trafigi FROM uyeler u, odunc_al_ver o WHERE (u.id = o.uye_id) GROUP BY u.uye_no, u.ad, u.soyad, u.uyelik_tarihi ORDER BY count(*) DESC;


ALTER TABLE public.encokokuyan OWNER TO kutya;

--
-- TOC entry 1227 (class 1259 OID 17691)
-- Dependencies: 1304 211 211 211 5
-- Name: getirilmeyenler; Type: VIEW; Schema: public; Owner: kutya
--

CREATE VIEW getirilmeyenler AS
    SELECT uyeler.uye_no, uyeler.ad, uyeler.soyad, kitaplar.ad AS kitap, odunc_al_ver.verme_tarihi AS vermetarihi, odunc_al_ver.alma_tarihi AS almatarihi FROM kitaplar, odunc_al_ver, uyeler WHERE (((odunc_al_ver.verdi_vermedi = false) AND (kitaplar.id = odunc_al_ver.kitap_id)) AND (uyeler.id = odunc_al_ver.uye_id));


ALTER TABLE public.getirilmeyenler OWNER TO kutya;

--
-- TOC entry 1229 (class 1259 OID 17696)
-- Dependencies: 211 210 5
-- Name: kitapgirissekli; Type: TABLE; Schema: public; Owner: kutya; Tablespace: 
--

CREATE TABLE kitapgirissekli (
    id serial NOT NULL,
    ad isim NOT NULL,
    ek ek_bilgi
);


ALTER TABLE public.kitapgirissekli OWNER TO kutya;

--
-- TOC entry 1635 (class 0 OID 0)
-- Dependencies: 1228
-- Name: kitapgirissekli_id_seq; Type: SEQUENCE SET; Schema: public; Owner: kutya
--

SELECT pg_catalog.setval(pg_catalog.pg_get_serial_sequence('kitapgirissekli', 'id'), 11, true);


--
-- TOC entry 1636 (class 0 OID 0)
-- Dependencies: 1213
-- Name: kitapkategori_id_seq; Type: SEQUENCE SET; Schema: public; Owner: kutya
--

SELECT pg_catalog.setval(pg_catalog.pg_get_serial_sequence('kitapkategori', 'id'), 17, true);


--
-- TOC entry 1637 (class 0 OID 0)
-- Dependencies: 1215
-- Name: kitaplar_id_seq; Type: SEQUENCE SET; Schema: public; Owner: kutya
--

SELECT pg_catalog.setval(pg_catalog.pg_get_serial_sequence('kitaplar', 'id'), 51, true);


--
-- TOC entry 1638 (class 0 OID 0)
-- Dependencies: 1219
-- Name: odunc_al_ver_id_seq; Type: SEQUENCE SET; Schema: public; Owner: kutya
--

SELECT pg_catalog.setval(pg_catalog.pg_get_serial_sequence('odunc_al_ver', 'id'), 38, true);


--
-- TOC entry 1639 (class 0 OID 0)
-- Dependencies: 1218
-- Name: odunc_al_ver_kitap_id_seq; Type: SEQUENCE SET; Schema: public; Owner: kutya
--

SELECT pg_catalog.setval(pg_catalog.pg_get_serial_sequence('odunc_al_ver', 'kitap_id'), 1, false);


--
-- TOC entry 1640 (class 0 OID 0)
-- Dependencies: 1217
-- Name: odunc_al_ver_uye_id_seq; Type: SEQUENCE SET; Schema: public; Owner: kutya
--

SELECT pg_catalog.setval(pg_catalog.pg_get_serial_sequence('odunc_al_ver', 'uye_id'), 1, false);


--
-- TOC entry 1231 (class 1259 OID 17704)
-- Dependencies: 210 5
-- Name: sinif; Type: TABLE; Schema: public; Owner: kutya; Tablespace: 
--

CREATE TABLE sinif (
    id serial NOT NULL,
    ad character varying(25) NOT NULL,
    ek ek_bilgi
);


ALTER TABLE public.sinif OWNER TO kutya;

--
-- TOC entry 1641 (class 0 OID 0)
-- Dependencies: 1230
-- Name: sinif_id_seq; Type: SEQUENCE SET; Schema: public; Owner: kutya
--

SELECT pg_catalog.setval(pg_catalog.pg_get_serial_sequence('sinif', 'id'), 16, true);


--
-- TOC entry 1642 (class 0 OID 0)
-- Dependencies: 1224
-- Name: uyeler_id_seq; Type: SEQUENCE SET; Schema: public; Owner: kutya
--

SELECT pg_catalog.setval(pg_catalog.pg_get_serial_sequence('uyeler', 'id'), 39, true);


--
-- TOC entry 1643 (class 0 OID 0)
-- Dependencies: 1221
-- Name: yayinevi_id_seq; Type: SEQUENCE SET; Schema: public; Owner: kutya
--

SELECT pg_catalog.setval(pg_catalog.pg_get_serial_sequence('yayinevi', 'id'), 8, true);


--
-- TOC entry 1234 (class 1259 OID 17714)
-- Dependencies: 5
-- Name: yazar_kitap; Type: TABLE; Schema: public; Owner: kutya; Tablespace: 
--

CREATE TABLE yazar_kitap (
    yazar_id serial NOT NULL,
    kitap_id serial NOT NULL
);


ALTER TABLE public.yazar_kitap OWNER TO kutya;

--
-- TOC entry 1644 (class 0 OID 0)
-- Dependencies: 1233
-- Name: yazar_kitap_kitap_id_seq; Type: SEQUENCE SET; Schema: public; Owner: kutya
--

SELECT pg_catalog.setval(pg_catalog.pg_get_serial_sequence('yazar_kitap', 'kitap_id'), 1, false);


--
-- TOC entry 1645 (class 0 OID 0)
-- Dependencies: 1232
-- Name: yazar_kitap_yazar_id_seq; Type: SEQUENCE SET; Schema: public; Owner: kutya
--

SELECT pg_catalog.setval(pg_catalog.pg_get_serial_sequence('yazar_kitap', 'yazar_id'), 1, false);


--
-- TOC entry 1236 (class 1259 OID 17720)
-- Dependencies: 210 5
-- Name: yazarlar; Type: TABLE; Schema: public; Owner: kutya; Tablespace: 
--

CREATE TABLE yazarlar (
    id serial NOT NULL,
    ad character varying(50) NOT NULL,
    soyad character varying(50) NOT NULL,
    ek ek_bilgi
);


ALTER TABLE public.yazarlar OWNER TO kutya;

--
-- TOC entry 1646 (class 0 OID 0)
-- Dependencies: 1235
-- Name: yazarlar_id_seq; Type: SEQUENCE SET; Schema: public; Owner: kutya
--

SELECT pg_catalog.setval(pg_catalog.pg_get_serial_sequence('yazarlar', 'id'), 3, true);


--
-- TOC entry 1627 (class 0 OID 17696)
-- Dependencies: 1229
-- Data for Name: kitapgirissekli; Type: TABLE DATA; Schema: public; Owner: kutya
--

INSERT INTO kitapgirissekli VALUES (0, 'Diğer', 'Bunu Silmeyiniz.');
INSERT INTO kitapgirissekli VALUES (9, 'Hediye', '');
INSERT INTO kitapgirissekli VALUES (10, 'Bağış', '');
INSERT INTO kitapgirissekli VALUES (11, 'Satın Alma', '');


--
-- TOC entry 1622 (class 0 OID 17634)
-- Dependencies: 1214
-- Data for Name: kitapkategori; Type: TABLE DATA; Schema: public; Owner: kutya
--

INSERT INTO kitapkategori VALUES (0, 'Diğer', 'Bunu Silmeyiniz.');
INSERT INTO kitapkategori VALUES (12, 'Tez/Ödev', '');
INSERT INTO kitapkategori VALUES (13, E'Süreli Yayın \\ Dergi', '');
INSERT INTO kitapkategori VALUES (14, 'Ders Kitabı', '');
INSERT INTO kitapkategori VALUES (15, 'Ansiklopedi', '');
INSERT INTO kitapkategori VALUES (16, 'Cd DvD', '');
INSERT INTO kitapkategori VALUES (17, 'Okuma Kitabı', '');


--
-- TOC entry 1623 (class 0 OID 17642)
-- Dependencies: 1216
-- Data for Name: kitaplar; Type: TABLE DATA; Schema: public; Owner: kutya
--



--
-- TOC entry 1624 (class 0 OID 17660)
-- Dependencies: 1220
-- Data for Name: odunc_al_ver; Type: TABLE DATA; Schema: public; Owner: kutya
--



--
-- TOC entry 1628 (class 0 OID 17704)
-- Dependencies: 1231
-- Data for Name: sinif; Type: TABLE DATA; Schema: public; Owner: kutya
--

INSERT INTO sinif VALUES (0, 'Diğer', 'Eğer bir sınıf seçmezseniz varsayılan olarak "Diğer" adlı sınıf kaydedilir.Bunu Silmeyiniz.');
INSERT INTO sinif VALUES (13, '1. Sınıf', '');
INSERT INTO sinif VALUES (14, '2. Sınıf', '');
INSERT INTO sinif VALUES (15, '3. Sınıf', '');
INSERT INTO sinif VALUES (16, '4. Sınıf', '');


--
-- TOC entry 1626 (class 0 OID 17680)
-- Dependencies: 1225
-- Data for Name: uyeler; Type: TABLE DATA; Schema: public; Owner: kutya
--



--
-- TOC entry 1625 (class 0 OID 17669)
-- Dependencies: 1222
-- Data for Name: yayinevi; Type: TABLE DATA; Schema: public; Owner: kutya
--

INSERT INTO yayinevi VALUES (0, 'Diğer', 'Eğer bir yayıncı seçmezseniz varsayılan olarak "Diğer" adlı yayınevi kaydedilir.
Bunu Silmeyiniz.');


--
-- TOC entry 1629 (class 0 OID 17714)
-- Dependencies: 1234
-- Data for Name: yazar_kitap; Type: TABLE DATA; Schema: public; Owner: kutya
--



--
-- TOC entry 1630 (class 0 OID 17720)
-- Dependencies: 1236
-- Data for Name: yazarlar; Type: TABLE DATA; Schema: public; Owner: kutya
--



--
-- TOC entry 1605 (class 2606 OID 17744)
-- Dependencies: 1229 1229
-- Name: pk_kitapgirissekli; Type: CONSTRAINT; Schema: public; Owner: kutya; Tablespace: 
--

ALTER TABLE ONLY kitapgirissekli
    ADD CONSTRAINT pk_kitapgirissekli PRIMARY KEY (id);


--
-- TOC entry 1585 (class 2606 OID 17746)
-- Dependencies: 1214 1214
-- Name: pk_kitapkategori; Type: CONSTRAINT; Schema: public; Owner: kutya; Tablespace: 
--

ALTER TABLE ONLY kitapkategori
    ADD CONSTRAINT pk_kitapkategori PRIMARY KEY (id);


--
-- TOC entry 1588 (class 2606 OID 17748)
-- Dependencies: 1216 1216
-- Name: pk_kitaplar; Type: CONSTRAINT; Schema: public; Owner: kutya; Tablespace: 
--

ALTER TABLE ONLY kitaplar
    ADD CONSTRAINT pk_kitaplar PRIMARY KEY (id);


--
-- TOC entry 1591 (class 2606 OID 17750)
-- Dependencies: 1220 1220 1220 1220
-- Name: pk_odunc_al_ver; Type: CONSTRAINT; Schema: public; Owner: kutya; Tablespace: 
--

ALTER TABLE ONLY odunc_al_ver
    ADD CONSTRAINT pk_odunc_al_ver PRIMARY KEY (uye_id, kitap_id, verme_tarihi);


--
-- TOC entry 1608 (class 2606 OID 17752)
-- Dependencies: 1231 1231
-- Name: pk_sinif; Type: CONSTRAINT; Schema: public; Owner: kutya; Tablespace: 
--

ALTER TABLE ONLY sinif
    ADD CONSTRAINT pk_sinif PRIMARY KEY (id);


--
-- TOC entry 1600 (class 2606 OID 17754)
-- Dependencies: 1225 1225
-- Name: pk_uyeler; Type: CONSTRAINT; Schema: public; Owner: kutya; Tablespace: 
--

ALTER TABLE ONLY uyeler
    ADD CONSTRAINT pk_uyeler PRIMARY KEY (id);


--
-- TOC entry 1594 (class 2606 OID 17756)
-- Dependencies: 1222 1222
-- Name: pk_yayinevi; Type: CONSTRAINT; Schema: public; Owner: kutya; Tablespace: 
--

ALTER TABLE ONLY yayinevi
    ADD CONSTRAINT pk_yayinevi PRIMARY KEY (id);


--
-- TOC entry 1610 (class 2606 OID 17758)
-- Dependencies: 1234 1234 1234
-- Name: pk_yazar_kitap; Type: CONSTRAINT; Schema: public; Owner: kutya; Tablespace: 
--

ALTER TABLE ONLY yazar_kitap
    ADD CONSTRAINT pk_yazar_kitap PRIMARY KEY (yazar_id, kitap_id);


--
-- TOC entry 1613 (class 2606 OID 17760)
-- Dependencies: 1236 1236
-- Name: pk_yazarlar; Type: CONSTRAINT; Schema: public; Owner: kutya; Tablespace: 
--

ALTER TABLE ONLY yazarlar
    ADD CONSTRAINT pk_yazarlar PRIMARY KEY (id);


--
-- TOC entry 1602 (class 2606 OID 17762)
-- Dependencies: 1225 1225
-- Name: uyeler_uye_no_key; Type: CONSTRAINT; Schema: public; Owner: kutya; Tablespace: 
--

ALTER TABLE ONLY uyeler
    ADD CONSTRAINT uyeler_uye_no_key UNIQUE (uye_no);


--
-- TOC entry 1596 (class 2606 OID 17764)
-- Dependencies: 1222 1222
-- Name: yayinevi_ad_key; Type: CONSTRAINT; Schema: public; Owner: kutya; Tablespace: 
--

ALTER TABLE ONLY yayinevi
    ADD CONSTRAINT yayinevi_ad_key UNIQUE (ad);


--
-- TOC entry 1603 (class 1259 OID 17765)
-- Dependencies: 1229 1229
-- Name: idx_kitapgirissekli___id_ad; Type: INDEX; Schema: public; Owner: kutya; Tablespace: 
--

CREATE INDEX idx_kitapgirissekli___id_ad ON kitapgirissekli USING btree (id, ad);


--
-- TOC entry 1583 (class 1259 OID 17766)
-- Dependencies: 1214 1214
-- Name: idx_kitapkategori___id_ad; Type: INDEX; Schema: public; Owner: kutya; Tablespace: 
--

CREATE INDEX idx_kitapkategori___id_ad ON kitapkategori USING btree (id, ad);


--
-- TOC entry 1586 (class 1259 OID 17767)
-- Dependencies: 1216
-- Name: idx_kitaplar___ad; Type: INDEX; Schema: public; Owner: kutya; Tablespace: 
--

CREATE INDEX idx_kitaplar___ad ON kitaplar USING btree (ad);


--
-- TOC entry 1589 (class 1259 OID 17768)
-- Dependencies: 1220
-- Name: idx_odunc_al_ver___verme_tarihi; Type: INDEX; Schema: public; Owner: kutya; Tablespace: 
--

CREATE INDEX idx_odunc_al_ver___verme_tarihi ON odunc_al_ver USING btree (verme_tarihi);


--
-- TOC entry 1606 (class 1259 OID 17769)
-- Dependencies: 1231
-- Name: idx_sinif___id; Type: INDEX; Schema: public; Owner: kutya; Tablespace: 
--

CREATE INDEX idx_sinif___id ON sinif USING btree (id);


--
-- TOC entry 1597 (class 1259 OID 17770)
-- Dependencies: 1225
-- Name: idx_uyeler___ad; Type: INDEX; Schema: public; Owner: kutya; Tablespace: 
--

CREATE INDEX idx_uyeler___ad ON uyeler USING btree (ad);


--
-- TOC entry 1598 (class 1259 OID 17771)
-- Dependencies: 1225
-- Name: idx_uyeler___soyad; Type: INDEX; Schema: public; Owner: kutya; Tablespace: 
--

CREATE INDEX idx_uyeler___soyad ON uyeler USING btree (soyad);


--
-- TOC entry 1592 (class 1259 OID 17772)
-- Dependencies: 1222
-- Name: idx_yayinevi___ad; Type: INDEX; Schema: public; Owner: kutya; Tablespace: 
--

CREATE INDEX idx_yayinevi___ad ON yayinevi USING btree (ad);


--
-- TOC entry 1611 (class 1259 OID 17773)
-- Dependencies: 1236 1236
-- Name: idx_yazarlar___ad_soyad; Type: INDEX; Schema: public; Owner: kutya; Tablespace: 
--

CREATE INDEX idx_yazarlar___ad_soyad ON yazarlar USING btree (ad, soyad);


--
-- TOC entry 1614 (class 2606 OID 17774)
-- Dependencies: 1216 1229 1604
-- Name: fk_kitaplar__kitapgirissekli_id; Type: FK CONSTRAINT; Schema: public; Owner: kutya
--

ALTER TABLE ONLY kitaplar
    ADD CONSTRAINT fk_kitaplar__kitapgirissekli_id FOREIGN KEY (giris_sekli) REFERENCES kitapgirissekli(id) ON UPDATE SET DEFAULT ON DELETE SET DEFAULT;


--
-- TOC entry 1615 (class 2606 OID 17779)
-- Dependencies: 1216 1214 1584
-- Name: fk_kitaplar__kitapkategori_id; Type: FK CONSTRAINT; Schema: public; Owner: kutya
--

ALTER TABLE ONLY kitaplar
    ADD CONSTRAINT fk_kitaplar__kitapkategori_id FOREIGN KEY (kategori) REFERENCES kitapkategori(id) ON UPDATE SET DEFAULT ON DELETE SET DEFAULT;


--
-- TOC entry 1616 (class 2606 OID 17784)
-- Dependencies: 1216 1222 1593
-- Name: fk_kitaplar__yayinevi_id; Type: FK CONSTRAINT; Schema: public; Owner: kutya
--

ALTER TABLE ONLY kitaplar
    ADD CONSTRAINT fk_kitaplar__yayinevi_id FOREIGN KEY (yayinci) REFERENCES yayinevi(id) ON UPDATE SET DEFAULT ON DELETE SET DEFAULT;


--
-- TOC entry 1617 (class 2606 OID 17789)
-- Dependencies: 1220 1216 1587
-- Name: fk_odunc_al_ver_kitaplar; Type: FK CONSTRAINT; Schema: public; Owner: kutya
--

ALTER TABLE ONLY odunc_al_ver
    ADD CONSTRAINT fk_odunc_al_ver_kitaplar FOREIGN KEY (kitap_id) REFERENCES kitaplar(id) ON UPDATE CASCADE ON DELETE CASCADE;


--
-- TOC entry 1618 (class 2606 OID 17794)
-- Dependencies: 1220 1225 1599
-- Name: fk_odunc_al_ver_uyeler; Type: FK CONSTRAINT; Schema: public; Owner: kutya
--

ALTER TABLE ONLY odunc_al_ver
    ADD CONSTRAINT fk_odunc_al_ver_uyeler FOREIGN KEY (uye_id) REFERENCES uyeler(id) ON UPDATE CASCADE ON DELETE CASCADE;


--
-- TOC entry 1619 (class 2606 OID 17799)
-- Dependencies: 1225 1231 1607
-- Name: fk_uyeler__sinif_id; Type: FK CONSTRAINT; Schema: public; Owner: kutya
--

ALTER TABLE ONLY uyeler
    ADD CONSTRAINT fk_uyeler__sinif_id FOREIGN KEY (sinif) REFERENCES sinif(id) ON UPDATE SET DEFAULT ON DELETE SET DEFAULT;


--
-- TOC entry 1620 (class 2606 OID 17804)
-- Dependencies: 1234 1216 1587
-- Name: fk_yazar_kitap__kitaplar_id; Type: FK CONSTRAINT; Schema: public; Owner: kutya
--

ALTER TABLE ONLY yazar_kitap
    ADD CONSTRAINT fk_yazar_kitap__kitaplar_id FOREIGN KEY (kitap_id) REFERENCES kitaplar(id) ON UPDATE CASCADE ON DELETE CASCADE;


--
-- TOC entry 1621 (class 2606 OID 17809)
-- Dependencies: 1234 1236 1612
-- Name: fk_yazar_kitap__yazarlar_id; Type: FK CONSTRAINT; Schema: public; Owner: kutya
--

ALTER TABLE ONLY yazar_kitap
    ADD CONSTRAINT fk_yazar_kitap__yazarlar_id FOREIGN KEY (yazar_id) REFERENCES yazarlar(id) ON UPDATE CASCADE ON DELETE CASCADE;


--
-- TOC entry 1634 (class 0 OID 0)
-- Dependencies: 5
-- Name: public; Type: ACL; Schema: -; Owner: postgres
--

REVOKE ALL ON SCHEMA public FROM PUBLIC;
REVOKE ALL ON SCHEMA public FROM postgres;
GRANT ALL ON SCHEMA public TO postgres;
GRANT ALL ON SCHEMA public TO PUBLIC;


-- Completed on 2008-07-27 19:02:51 EEST

--
-- PostgreSQL database dump complete
--

