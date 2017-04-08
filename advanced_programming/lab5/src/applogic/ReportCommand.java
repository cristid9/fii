package applogic;

import net.sf.dynamicreports.jasper.builder.export.JasperPdfExporterBuilder;
import net.sf.dynamicreports.report.exception.DRException;
import net.sf.jasperreports.engine.JRDataSource;
import net.sf.jasperreports.engine.data.JRBeanCollectionDataSource;
import org.apache.poi.hssf.usermodel.HSSFCell;
import org.apache.poi.hssf.usermodel.HSSFRow;
import org.apache.poi.hssf.usermodel.HSSFSheet;
import org.apache.poi.hssf.usermodel.HSSFWorkbook;
import org.apache.velocity.Template;
import org.apache.velocity.VelocityContext;
import org.apache.velocity.app.VelocityEngine;

import java.io.*;
import java.util.List;
import java.util.Properties;

import static net.sf.dynamicreports.report.builder.DynamicReports.*;

public class ReportCommand extends AbstractCommand implements Command {
    public ReportCommand() {
        super();
    }

    static final String HTML_REPORT = "html";
    static final String PDF_REPORT = "pdf";
    static final String EXCEL_REPORT = "excel";

    @Override
    public void doExecute(Catalog catalog) throws IOException {

        if (commandArgs.get(1).equals(HTML_REPORT)) {


            Properties props = new Properties();
            props.put("file.resource.loader.path", "/home/cristi/java/lab4/src");

            VelocityEngine ve = new VelocityEngine(props);
            ve.init();

            Template t = ve.getTemplate("template.vm");

            VelocityContext ctx = new VelocityContext();

            ctx.put("items", catalog.getItems());

            StringWriter writer = new StringWriter();
            t.merge(ctx, writer);

            FileWriter fw = new FileWriter("/home/cristi/java/lab4/src/report.html");
            BufferedWriter bw = new BufferedWriter(fw);
            bw.write(writer.toString());
            bw.close();

        } else if (commandArgs.get(1).equals(PDF_REPORT)) {


            JasperPdfExporterBuilder exporterBuilder = export.pdfExporter("/home/cristi/java/lab4/src/report.pdf");
            JRDataSource dataSource = new JRBeanCollectionDataSource(catalog.getItems());

            try {
                report()
                        .columns(col.column("Item", "itemName", type.stringType()))
                        .setDataSource(dataSource)
                        .toPdf(exporterBuilder);
            } catch (DRException e) {
                e.printStackTrace();
            }

        } else if (commandArgs.get(1).equals(EXCEL_REPORT)) {
            HSSFWorkbook workbook = new HSSFWorkbook();
            HSSFSheet sheet = workbook.createSheet("Report");

            int rowCount = 0;
            for (CatalogItem item : catalog.getItems()) {
                HSSFRow row = sheet.createRow(++rowCount);

                HSSFCell cell = row.createCell(0);
                cell.setCellValue(item.getItemName());

                HSSFCell cell2 = row.createCell(1);
                cell2.setCellValue(item.getItemPath());
            }

            try {
                FileOutputStream fo = new FileOutputStream("/home/cristi/java/lab4/src/report.xlsx");
                workbook.write(fo);
            } catch (FileNotFoundException e) {
                e.printStackTrace();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }

    }

    @Override
    public void loadArgs(List<String> args) {
        this.commandArgs = args;
    }
}
