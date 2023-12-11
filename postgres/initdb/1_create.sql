CREATE TABLE IF NOT EXISTS score (
    id          serial      not null primary key,
    version_id  int         not null default 0,
    name        text        not null default '名無し',
    score       int         not null default 0,
    created_at  timestamp   not null default current_timestamp
);
CREATE TABLE IF NOT EXISTS version (
    id          serial      not null primary key,
    name        text        not null default 'new version',
    created_at  timestamp   not null default current_timestamp
);
INSERT INTO version (name) values ('beta_v1.0');
INSERT INTO version (name) values ('beta_v1.1');
INSERT INTO version (name) values ('beta_v1.2');