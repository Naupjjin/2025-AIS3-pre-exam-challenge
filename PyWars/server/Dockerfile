FROM python:3.9-slim

WORKDIR /app

# Copy requirements first for better caching
COPY ./src/requirements.txt .
RUN pip install --no-cache-dir -r requirements.txt

# Copy the rest of the application
COPY ./src /app

# Create uploads directory
RUN mkdir -p /app/uploads

# Set proper permissions
RUN chmod -R 755 /app

# Make port 10000 available
EXPOSE 10000

# Run the application
CMD ["python3", "server.py"]