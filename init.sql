CREATE TABLE IF NOT EXISTS sensor_data (
    timestamp TIMESTAMPTZ NOT NULL,
    temperature DOUBLE PRECISION,
    humidity DOUBLE PRECISION,
    motion BOOLEAN,
    PRIMARY KEY (timestamp)
);

SELECT create_hypertable('sensor_data', 'timestamp', if_not_exists => TRUE);
