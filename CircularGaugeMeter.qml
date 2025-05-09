import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Shapes 1.15

Item {
    id: gauge
    property bool shadowVisible: true
    property real outerRadius: 100
    property real value: 120  // Giá trị thay đổi của gauge
    property real maximumValue: 240  // Tự định nghĩa maximumValue nếu không có sẵn
    property real minimumValue: 2

    // Không sử dụng style nữa, thay vào đó sử dụng các thành phần tùy chỉnh
    Rectangle {
        implicitHeight: gauge.height
        implicitWidth: gauge.width
        color: "transparent"
        anchors.centerIn: parent
        radius: 360

        Canvas {
            visible: gauge.shadowVisible
            property int value: gauge.value
            anchors.fill: parent
            opacity: 0.03
            onValueChanged: requestPaint()

            function degreesToRadians(degrees) {
                return degrees * (Math.PI / 180);
            }

            function createLinearGradient(ctx, start, end, colors) {
                var gradient = ctx.createLinearGradient(start.x, start.y, end.x, end.y);
                for (var i = 0; i < colors.length; i++) {
                    gradient.addColorStop(i / (colors.length - 1), colors[i]);
                }
                return gradient;
            }

            onPaint: {
                var ctx = getContext("2d");
                ctx.reset();

                // Định nghĩa các màu sắc cho gradient
                var gradientColors = [
                    "#D9D9D9", // Màu bắt đầu
                    "#D9D9D9"  // Màu kết thúc
                ];




                var gradient = createLinearGradient(ctx, { x: 0, y: 0 }, { x: outerRadius * 2, y: 0 }, gradientColors);

                // Loop qua các màu sắc và vẽ các đoạn vòng cung
                for (var i = 0; i < gradientColors.length; i++) {
                    var gradientColor = gradientColors[i];
                    //var angle = startAngle + (endAngle - startAngle) * (i / (gradientColors.length - 1));

                    ctx.beginPath();
                    ctx.lineWidth = outerRadius * 0.15;
                    ctx.strokeStyle = gradient;
                    ctx.arc(outerRadius, outerRadius, outerRadius - 48, degreesToRadians(angle), degreesToRadians(endAngle));
                    ctx.stroke();
                }
            }
        }
    }


}
