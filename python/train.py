import torch
from ultralytics import YOLO
import os

def train_conveyor_model():
    if torch.backends.mps.is_available():
        device = "mps"
    elif torch.cuda.is_available():
        device = "0"
    else:
        device = "cpu"

    print(f"Using Device: {device}")

    model = YOLO('yolo11n.pt')

    result = model.train(
        data='/Users/pratik/Documents/Finalized Projects/ConveyorVision/datasets/flower_dataset/data.yaml',
        epochs=2,
        imgsz=640,
        device=device,
        freeze=10,
        plots=True)
    
    path = model.export(format='onnx', dynamic=True)
    print(f"Model exported to {path}")

if __name__ == "__main__":
    train_conveyor_model()