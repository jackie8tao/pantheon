create database tdfblog character set utf8mb4 collate utf8mb4_general_ci;

# 用户信息表
create table users
(
    id         int auto_increment key not null comment '用户ID',
    nickname   varchar(64) unique     not null comment '昵称',
    avatar     varchar(256)           null comment '头像url',
    created_at timestamp              not null default current_timestamp comment '创建时间',
    updated_at timestamp              not null default current_timestamp on update current_timestamp comment '更新时间',
    deleted_at timestamp              null comment '删除时间'
) engine InnoDB
  character set utf8mb4
  collate utf8mb4_general_ci comment '用户信息表';

# 帖子表
create table posts
(
    id         bigint auto_increment not null comment '帖子ID',
    uid        int                   not null comment '用户ID',
    title      varchar(256)          not null comment '标题',
    content    text                  not null comment '内容',
    created_at timestamp             not null default current_timestamp comment '创建时间',
    updated_at timestamp             not null default current_timestamp on update current_timestamp comment '更新时间',
    deleted_at timestamp             null comment '删除时间',
    constraint primary key (id)
) engine InnoDB
  character set utf8mb4
  collate utf8mb4_general_ci comment '帖子信息表';

# 网站配置
create table configs
(
    id         int auto_increment not null comment 'ID',
    `key`      varchar(64)        not null comment '配置键',
    value      varchar(128)       not null comment '配置值',
    created_at timestamp          not null default current_timestamp comment '创建时间',
    updated_at timestamp          not null default current_timestamp on update current_timestamp comment '更新时间',
    deleted_at timestamp          null comment '删除时间',
    primary key (id),
    constraint unique (`key`)
) engine InnoDB
  character set utf8mb4
  collate utf8mb4_general_ci comment '网站配置表';